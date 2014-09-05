#include <iostream>
#include <array>
#include <list>
#include <algorithm>

/** @brief Typedef for money type. */
typedef float Money;

/**
 * @brief MonthsInvestment enum.
 * @details These are the possible investment months.
 */
enum MonthsInvestment
{
    ONE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGTH,
    NINE,
    TEN,
    ELEVEN,
    TWELVE
};

/** @brief Typedefs for rate and table of rates types. */
typedef float Rate;
typedef std::array<Rate, TWELVE> RatesTable;

/** @brief Typedefs for investment actions. */
typedef MonthsInvestment Action;
typedef std::list<Action> Actions;

/**
 * @brief InvestmentFunction class.
 * @details This class is responsible to calculate profits.
 */
class InvestmentFunction
{
public:

    /**
     * @brief Constructor.
     * @param[in] ratesTable Rates table.
     */
    InvestmentFunction(const RatesTable& ratesTable) :
        _ratesTable(ratesTable)
    {}

    /**
     * @brief Executes a single shot investment action.
     * @param[in] initialAmount Initial amount of money.
     * @param[in] investmentPerMonth Amount of money to invest per month.
     * @param[in] months The month type of the investment.
     * @return The total profits of the execution.
     */
    Money execute(Money initialAmount, Money investmentPerMonth, MonthsInvestment months) const
    {
        Money monthsSum(0.f);
        for (MonthsInvestment i = months; i > 0;)
        {
            monthsSum += _getRate(i);
            i = MonthsInvestment(i - 1);
        }

        return initialAmount * _getRate(months) + investmentPerMonth * monthsSum;
    }

    /**
     * @brief Executes many times an investment action.
     * @param[in] initialAmount Initial amount of money.
     * @param[in] investmentPerMonth Amount of money to invest per month.
     * @param[in] months The month type of the investment.
     * @param[in] times The times to do this operation.
     * @return The total profits of the execution.
     */
    Money execute(Money initialAmount, Money investmentPerMonth, MonthsInvestment months, unsigned int times) const
    {
        Money total(initialAmount);
        for (unsigned int i = 0u; i < times; ++i)
        {
            total = execute(total, investmentPerMonth, months);
        }

        return total;
    }

    /**
     * @brief Gets the best choice of investment.
     * @param[in] initialAmount Initial amount of money.
     * @param[in] investmentPerMonth Amount of money to invest per month.
     * @param[in] totalMonthsOfInvestment The total projected months of the inversion.
     * @param[out] actions The best actions to do.
     * @return The best profits.
     */
    Money getBest(Money initialAmount, Money investmentPerMonth, unsigned int totalMonthsOfInvestment,
                  Actions& actions) const
    {
        Money maxBenefits(initialAmount);
        if(totalMonthsOfInvestment > 0)
        {
            Actions bestActions;
            for (MonthsInvestment m = ONE; m <= std::min(totalMonthsOfInvestment, unsigned(TWELVE));)
            {
                Money currentBenefits = execute(initialAmount, investmentPerMonth, m);
                Actions currentActions = actions;
                currentActions.emplace_back(m);
                currentBenefits = getBest(currentBenefits, investmentPerMonth, totalMonthsOfInvestment - m,
                                           currentActions);

                if (currentBenefits > maxBenefits)
                {
                    maxBenefits = currentBenefits;
                    bestActions = currentActions;
                }

                // Advance to the next investment month.
                m = MonthsInvestment(m + 1);
            }
            actions = bestActions;
        }

        return maxBenefits;
    }

private:

    /**
     * @brief Gets the inversion rate given a month type of investment.
     * @param[in] months Month type of investment.
     * @return The inversion rate.
     */
    inline Rate _getRate(MonthsInvestment months) const
    {
        return _ratesTable[months-1];
    }

    /** @brief The rates table. */
    const RatesTable _ratesTable;
};


int main()
{
    const RatesTable hsbcTable =
    {
        1.f + 20.f   / 12.f / 100.f,
        1.f + 20.75f / 12.f / 100.f * 2,
        1.f + 21.5f  / 12.f / 100.f * 3,
        1.f + 22.25f / 12.f / 100.f * 4,
        1.f + 23.f   / 12.f / 100.f * 5,
        1.f + 23.75f / 12.f / 100.f * 6,
        1.f + 23.75f / 12.f / 100.f * 7,
        1.f + 23.75f / 12.f / 100.f * 8,
        1.f + 23.75f / 12.f / 100.f * 9,
        1.f + 23.75f / 12.f / 100.f * 10,
        1.f + 23.75f / 12.f / 100.f * 11,
        1.f + 24.5f  / 12.f / 100.f * 12
    };

    InvestmentFunction hsbcInvFunction(hsbcTable);
    const Money initialValue = 27093.5f;
    const Money investPM = 2000.f;

    std::cout << hsbcInvFunction.execute(0, investPM, TWELVE, 1u) << std::endl;
    std::cout << hsbcInvFunction.execute(0, investPM, SIX, 2u) << std::endl;
    std::cout << hsbcInvFunction.execute(0, investPM, FOUR, 3u) << std::endl;
    std::cout << hsbcInvFunction.execute(0, investPM, THREE, 4u) << std::endl;
    std::cout << hsbcInvFunction.execute(0, investPM, TWO, 6u) << std::endl;
    std::cout << hsbcInvFunction.execute(0, investPM, ONE, 12u) << std::endl;

    Actions actions;
    const Money bestProfit = hsbcInvFunction.getBest(0, investPM, 12u, actions);
    std::cout << "Best profit: " << bestProfit << std::endl;

    unsigned int op(0u);
    for(Action action : actions)
    {
        std::cout << "Action " << ++op << " : do the inversion to " << action << " months." << std::endl;
    }

    return 0;
}
