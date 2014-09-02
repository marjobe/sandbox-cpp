#include <iostream>
#include <fstream>

class TextFileReader
{
public:

    ~TextFileReader()
    {
        close();
    }

    inline bool open(const std::string& filename)
    {
        close();
        _inputFile.open(filename, std::ios::out);
    }

    inline void close()
    {
        if (_inputFile.is_open())
            _inputFile.close();
    }

    inline bool eof() const
    {
        return _inputFile.eof();
    }

    template<typename T>
    inline bool getNext(T& t)
    {
        _inputFile >> t;
        return !_inputFile.fail();
    }

private:

    std::ifstream _inputFile;
};

template<typename T, unsigned int M, unsigned int N>
struct CardShow
{
    T table[M][N];

    void print()
    {
        for (unsigned int i = 0; i < M; ++i)
        {
            for (unsigned int j = 0; j < N; ++j)
            {
                std::cout << table[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }
};

template<typename T, unsigned int M, unsigned int N>
class GamePlay
{
public:

    void pushInfo(const CardShow<T, M, N>& firstCards, unsigned int firstRowChoosen,
                  const CardShow<T, M, N>& secondCards, unsigned int secondRowChoosen)
    {
        _firstCards = firstCards;
        _firstRowChoosen = firstRowChoosen;
        _secondCards = secondCards;
        _secondRowChoosen = secondRowChoosen;
    }

    enum class Result
    {
        OK,
        BadMagician,
        VolunteerCheated
    };

    Result play(T& card)
    {
        unsigned int count(0u);
        for (unsigned int firstJ = 0u; firstJ < N; ++firstJ)
        {
            for (unsigned int j = 0u; j < N; ++j)
            {
                if(_secondCards.table[_secondRowChoosen][j] == _firstCards.table[_firstRowChoosen][firstJ])
                {
                    ++count;
                    card = _secondCards.table[_secondRowChoosen][j];
                }
            }
        }

        Result result;
        if (count == 1u)
        {
            result = Result::OK;
        }
        else if (count > 1u)
        {
            result = Result::BadMagician;
        }
        else //if (count == 0u)
        {
            result = Result::VolunteerCheated;
        }

        return result;
    }

private:

    CardShow<T, M, N>   _firstCards;
    unsigned int        _firstRowChoosen;
    CardShow<T, M, N>   _secondCards;
    unsigned int        _secondRowChoosen;
};

int main ()
{
    TextFileReader tfr;
    //tfr.open("example.txt");
    tfr.open("A-small-practice.in");

    unsigned int testsNumber;
    if (tfr.getNext(testsNumber))
    {
        GamePlay<int, 4, 4> gamePlay;
        for (unsigned int i = 0u; i < testsNumber; ++i)
        {
            unsigned int firstRowChoosen;
            tfr.getNext(firstRowChoosen);
            --firstRowChoosen;

            CardShow<int, 4, 4> firstCards;
            for (unsigned int i = 0; i < 4; ++i)
            {
                for (unsigned int j = 0; j < 4; ++j)
                {
                    tfr.getNext(firstCards.table[i][j]);
                }
            }
            //firstCards.print();

            unsigned int secondRowChoosen;
            tfr.getNext(secondRowChoosen);
            --secondRowChoosen;

            CardShow<int, 4, 4> secondCards;
            for (unsigned int i = 0; i < 4; ++i)
            {
                for (unsigned int j = 0; j < 4; ++j)
                {
                    tfr.getNext(secondCards.table[i][j]);
                }
            }
            //secondCards.print();

            gamePlay.pushInfo(firstCards, firstRowChoosen, secondCards, secondRowChoosen);

            std::cout << "Case #" << i + 1 << ": ";
            int card;
            switch (gamePlay.play(card))
            {
                case GamePlay<int, 4, 4>::Result::OK :
                    std::cout << card;
                    break;
                case GamePlay<int, 4, 4>::Result::BadMagician :
                    std::cout << "Bad magician!";
                    break;
                case GamePlay<int, 4, 4>::Result::VolunteerCheated :
                    std::cout << "Volunteer cheated!";
                    break;
            }
            std::cout << std::endl;
        }
        
    }


    return 0;
}