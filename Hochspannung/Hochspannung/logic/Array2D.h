#ifndef _ARRAY_2D_H_
#define _ARRAY_2D_H_

#include <xutility>
#include <functional>

template<typename T>
class Array2D
{
private:
	//This class is just supposed to be a helper class for the Array2D class
	//Needs to be an private inner class so that the user can't instantiate objects from it
	template<typename TT>
	class Array1D
	{
	private:
		TT* row;
#ifdef _DEBUG
		size_t cols;
#endif

	public:
#ifdef _DEBUG
		inline Array1D(TT* row, const size_t cols)
			: row(row), cols(cols)
		{}
#else
		inline Array1D(TT* row)
			: row(row)
		{}
#endif
		inline ~Array1D()
		{}

		inline TT& operator[](const size_t colIdx)
		{
#ifdef _DEBUG
			if (colIdx >= cols) {
				std::_Xout_of_range("colIdx is out of range");
			}
#endif
			return row[colIdx];
		}
		inline const TT& operator[](const size_t colIdx) const
		{
#ifdef _DEBUG
			if (colIdx >= cols) {
				std::_Xout_of_range("colIdx is out of range");
			}
#endif
			return row[colIdx];
		}
	};

private:
	T* data;
	size_t rows;
#ifdef _DEBUG
	size_t cols;
#endif

public:
	inline Array2D(const size_t rows, const size_t cols, const std::function<void(T& obj)>& callback = nullptr)
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
	inline Array2D(const size_t rows, const size_t cols, const T& defaultValue)
		: Array2D(rows, cols)
	{
		for (size_t i = 0; i < rows*cols; i++) {
			data[i] = defaultValue;
		}
	}
	inline ~Array2D()
	{
		delete[] data;
	}

	//It is not possible to copy objects of this class, because the length is never stored
	inline Array2D(const Array2D& src) = delete;
	inline Array2D& operator=(const Array2D& src) = delete;

	//But the object can be moved
	inline Array2D& operator=(Array2D&& src)
	{
		if (this != &src) {
			//Swap data so that the old values from this will be deleted
			T* tmp = this->data;
			this->data = src.data;
			src.data = tmp;

			this->rows = src.rows;
#ifdef _DEBUG
			this->cols = src.cols;
#endif
		}

		return *this;
	}
	inline Array2D(Array2D&& src)
	{
		this->data = src.data;
		this->rows = src.rows;
#ifdef _DEBUG
		this->cols = src.cols;
#endif
		//Don't delete the data from the source
		src.data = nullptr;
	}

	inline Array1D<T> operator[](const size_t rowIdx)
	{
#ifdef _DEBUG
		if (rowIdx >= rows) {
			std::_Xout_of_range("rowIdx is out of range");
		}

		return Array1D<T>(&data[rowIdx * rows], cols);
#else
		return Array1D<T>(&data[rowIdx * rows]);
#endif
	}
	inline const Array1D<T> operator[](const size_t rowIdx) const
	{
#ifdef _DEBUG
		if (rowIdx >= rows) {
			std::_Xout_of_range("rowIdx is out of range");
		}

		return Array1D<T>(&data[rowIdx * rows], cols);
#else
		return Array1D<T>(&data[rowIdx * rows]);
#endif
	}

	inline size_t getRows() const
	{
		return rows;
	}
};

#endif //_ARRAY_2D_H_
