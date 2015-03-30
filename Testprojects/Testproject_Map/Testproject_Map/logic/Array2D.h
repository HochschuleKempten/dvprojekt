#ifndef _ARRAY_2D_H_
#define _ARRAY_2D_H_

#include <xutility>

template<typename T>
class Array2D
{
private:
	//This class is just supposed to be a helper class for the Array2D class
	//Needs to be an inner class so that the user can't instantiate objects from it
	template<typename T>
	class Array1D
	{
	private:
		T* row;
#ifdef _DEBUG
		size_t cols;
#endif

	public:
#ifdef _DEBUG
		inline Array1D(T* row, const size_t cols)
			: row(row), cols(cols)
		{}
#endif
		inline Array1D(T* row)
			: row(row)
		{}
		inline ~Array1D()
		{}

		inline T& operator[](const size_t colIdx)
		{
#ifdef _DEBUG
			if (colIdx >= cols) {
				std::_Xout_of_range("colIdx is out of range");
			}
#endif
			return row[colIdx];
		}
		inline const T& operator[](const size_t colIdx) const
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
	inline Array2D(const size_t rows, const size_t cols)
		: data(new T[rows*cols]), rows(rows)
#ifdef _DEBUG
		, cols(cols)
#endif
	{}
	inline Array2D(const size_t rows, const size_t cols, const T& default)
		: Array2D(rows, cols)
	{
		for (size_t i = 0; i < rows*cols; i++) {
			data[i] = T();
		}
	}
	inline ~Array2D()
	{
		delete[] data;
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
