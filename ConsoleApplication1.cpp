#include <iostream>
#include <iomanip>
using namespace std;

class image {
private:
    int m_rows, m_cols;
    bool* binaryElements;

    int checkType(int value)
    {
        if (isdigit(value)) {
            throw - 1;
        }
        return value;
    }
public:
    image() {
        m_rows = 0;
        m_cols = 0;
        binaryElements = nullptr;
    }

    image(int rows, int cols) {
        m_rows = checkType(rows);
        m_cols = checkType(cols);
        binaryElements = new bool[m_cols * m_rows];
    }

    image(const image& other) {
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        binaryElements = new bool[m_cols * m_rows];
        for (int i = 0; i < m_rows * m_cols; ++i) {
            binaryElements[i] = other.binaryElements[i];
        }
    }

    ~image() {
        if (nullptr != binaryElements)
            delete[] binaryElements;
    }

    bool get(int i, int j) const {
        return binaryElements[i * m_cols + j];
    }

    void change(int i, int j, bool value) const {
        binaryElements[i * m_cols + j] = value;
    }

    bool can_multiply(const image& other) {
        return m_rows == other.m_rows && m_cols == other.m_cols;
    }

    image operator+(const image& other) {
        if (false == can_multiply(other)) {
            image empty;
            return empty;
        }
        image result(m_rows, m_cols);
        for (int i = 0; i < m_rows; i++) {
            for (int j = 0; j < other.m_cols; j++) {
                result.binaryElements[i * m_cols + j] = get(i, j) || other.get(i, j);
            }
        }
        return result;
    }

    bool read_keyboard() {
        if (binaryElements == nullptr) {
            cout << "memory not allocated";
            return false;
        }
        for (int i = 0; i < m_rows; ++i) {
            for (int j = 0; j < m_cols; ++j) {
                cout << "[" << i << "]" << "[" << j << "] = ";
                cin >> binaryElements[i * m_cols + j];
            }
        }
        return true;
    }

    void print_screen() {
        for (int i = 0; i < m_rows; ++i) {
            for (int j = 0; j < m_cols; ++j) {
                if (binaryElements[i * m_cols + j]) {
                    cout << fixed << "*" << " ";
                }
                else {
                    cout << fixed << " " << " ";
                }
            }
            cout << endl;
        }
    }

    bool equal_size(const image& other) {
        return m_rows == other.m_rows && m_cols == other.m_cols;
    }

    image operator*(const image& other) {
        if (false == can_multiply(other)) {
            image empty;
            return empty;
        }
        image result(m_rows, m_cols);
        for (int i = 0; i < m_rows; i++) {
            for (int j = 0; j < other.m_cols; j++) {
                result.binaryElements[i * m_cols + j] = get(i, j) && other.get(i, j);
            }
        }
        return result;
    }

    int rows() const {
        return m_rows;
    }

    int cols() const {
        return m_cols;
    }

    void resize(int rows, int cols) {
        m_rows = checkType(rows);
        m_cols = checkType(cols);
        if (binaryElements)
            delete[] binaryElements;
        binaryElements = new bool[m_rows * m_cols];
    }

    double fullness() {
        int fullness;
        for (int i = 0; i < m_rows; i++) {
            for (int j = 0; j < m_cols; j++) {
                if (get(i, j)) fullness++;
            }
        }
        return (double) fullness/(m_rows* m_cols);
    }

    image operator!() {
        image result(m_rows, m_cols);
        for (int i = 0; i < m_rows; i++) {
            for (int j = 0; j < m_cols; j++) {
                result.binaryElements[i * m_cols + j] = !get(i, j);
            }
        }
        return result;
    }

    image operator=(const image& other) {
        image result(other.m_rows, other.m_cols);
        for (int i = 0; i < other.m_rows; i++) {
            for (int j = 0; j < other.m_cols; j++) {
                result.binaryElements[i * m_cols + j] = other.get(i, j);
            }
        }
        return result;
    }

    image operator*(bool value) {
        image result(m_rows, m_cols);
        for (int i = 0; i < m_rows * m_cols; ++i) {
            result.binaryElements[i] = binaryElements[i] && value;
        }
    }

    image operator+(bool value) {
        image result(m_rows, m_cols);
        for (int i = 0; i < m_rows * m_cols; ++i) {
            result.binaryElements[i] = binaryElements[i] || value;
        }
        return result;
    }
};

image randomImage(int rows, int cols) {
    image image(rows, cols);
    for (int i = 0; i < image.rows(); ++i) {
        for (int j = 0; j < image.cols(); ++j) {
            image.change(i, j, rand() % 2);
        }
    }
    return image;
}

int main()
{
   image image = randomImage(10,10), image2 = randomImage(10, 10), image3 = randomImage(10, 10);
   image.print_screen();
   cout << "[Test]"<<endl;
   (!image).print_screen();
   cout << "[Test1]" << endl;
   cout << "[image]" << endl;
   image.print_screen();
   cout << "[image2]" << endl;
   image2.print_screen();
   cout << "[Result]" << endl;
   (image + image2).print_screen();
   cout << "[Test2]" << endl;
   cout << "[image3]" << endl;
   image3.print_screen(); 
   cout << "[image2]" << endl;
   image2.print_screen();
   cout << "[Result]" << endl;
   (image3*image2).print_screen();
}