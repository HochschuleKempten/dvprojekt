#ifndef _ARRAY_2D_H_
#define _ARRAY_2D_H_

#include "LUtility.h"
#include <functional>

template<typename T>
class DynArray2D
{
private:
	//This class is just supposed to be a helper class for the Array2D class
	//Needs to be an private inner class so that the user can't instantiate objects from it
	template<typename TT>
	class DynArray1D
	{
	private:
		TT* row;
		DEBUG_EXPRESSION(size_t cols);

	public:
#ifdef _DEBUG
		inline DynArray1D(TT* row, const size_t cols)
			: row(row), cols(cols)
		{}
#else
		inline DynArray1D(TT* row)
			: row(row)
		{}
#endif
		inline ~DynArray1D()
		{}

		inline TT& operator[](const size_t colIdx)
		{
			ASSERT(colIdx < cols, "colIdx is out of range");
			return row[colIdx];
		}
		inline const TT& operator[](const size_t colIdx) const
		{
			ASSERT(colIdx < cols, "colIdx is out of range");
			return row[colIdx];
		}
	};

private:
	T* data;
	size_t rows;
	DEBUG_EXPRESSION(size_t cols);

public:
	inline DynArray2D(const size_t rows, const size_t cols, const std::function<void(T& obj)>& callback = nullptr)
		: data(new T[rows*cols]), rows(rows)
#ifdef _DEBUG
		, cols(cols)
#endif
	{
		if (callback != nullptr) {
			for (size_t i = 0; i < rows*cols; i++) {
				callback(data[i]);
			}
		}
	}
	inline DynArray2D(const size_t rows, const size_t cols, const T& defaultValue)
		: DynArray2D(rows, cols)
	{
		for (size_t i = 0; i < rows*cols; i++) {
			data[i] = defaultValue;
		}
	}
	inline ~DynArray2D()
	{
		delete[] data;
	}

	//It is not possible to copy objects of this class, because the length is never stored
	inline DynArray2D(const DynArray2D& src) = delete;
	inline DynArray2D& operator=(const DynArray2D& src) = delete;

	//But the object can be moved
	inline DynArray2D& operator=(DynArray2D&& src)
	{
		if (this != &src) {
			//Swap data so that the old values from this will be deleted
			T* tmp = this->data;
			this->data = src.data;
			src.data = tmp;

			this->rows = src.rows;
			DEBUG_EXPRESSION(this->cols = src.cols);
		}

		return *this;
	}
	inline DynArray2D(DynArray2D&& src)
	{
		this->data = src.data;
		this->rows = src.rows;
		DEBUG_EXPRESSION(this->cols = src.cols);

		//Don't delete the data from the source
		src.data = nullptr;
	}

	inline DynArray1D<T> operator[](const size_t rowIdx)
	{
		ASSERT(rowIdx < rows, "rowIdx is out of range");

#ifdef _DEBUG
		return DynArray1D<T>(&data[rowIdx * rows], cols);
#else
		return DynArray1D<T>(&data[rowIdx * rows]);
#endif
	}
	inline const DynArray1D<T> operator[](const size_t rowIdx) const
	{
		ASSERT(rowIdx < rows, "rowIdx is out of range");

#ifdef _DEBUG
		return DynArray1D<T>(&data[rowIdx * rows], cols);
#else
		return DynArray1D<T>(&data[rowIdx * rows]);
#endif
	}

	inline size_t getRows() const
	{
		return rows;
	}
};

template<typename T, size_t rows, size_t cols>
class StatArray2D
{
private:
	template<typename TT>
	class StatArray1D
	{
	private:
		TT* row;

	public:
		explicit inline StatArray1D(TT* row)
			: row(row)
		{}
		inline ~StatArray1D()
		{}

		inline TT& operator[](const size_t colIdx)
		{
			ASSERT(colIdx < cols, "colIdx is out of range");
			return row[colIdx];
		}
		inline const TT& operator[](const size_t colIdx) const
		{
			ASSERT(colIdx < cols, "colIdx is out of range");
			return row[colIdx];
		}
	};

private:
	T data[rows*cols];

public:
	explicit inline StatArray2D(const std::function<void(T& obj)>& callback = nullptr)
	{
		if (callback != nullptr) {
			for (size_t i = 0; i < rows*cols; i++) {
				callback(data[i]);
			}
		}
	}
	inline ~StatArray2D()
	{}

	inline StatArray1D<T> operator[](const size_t rowIdx)
	{
		ASSERT(rowIdx < rows, "rowIdx is out of range");
		return StatArray1D<T>(&data[rowIdx * rows]);
	}
	inline const StatArray1D<const T> operator[](const size_t rowIdx) const
	{
		ASSERT(rowIdx < rows, "rowIdx is out of range");
		return StatArray1D<const T>(&data[rowIdx * rows]);
	}

	inline size_t getRows() const
	{
		return rows;
	}
	inline size_t getCols() const
	{
		return cols;
	}
};

#endif //_ARRAY_2D_H_
