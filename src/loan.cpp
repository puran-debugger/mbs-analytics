#include <stdexcept>
#include "loan.h"
#include "utilities.h"

Loan::Loan(std::string id,
           double originalBalance,
           double currentBalance,
           struct tm factorDate,
           int originalLoanTerm,
           int originalAmortTerm,
           int originalIOTerm,
           int currentLoanAge,
           double grossCoupon,
           double feeStrip,
           std::string originalPrepaymentString,
           std::experimental::optional<double> periodicDebtService,
           PaymentFrequency paymentFrequency) : id(id),
                                                originalBalance(originalBalance),
                                                currentBalance(currentBalance),
                                                factorDate(factorDate),
                                                originalLoanTerm(originalLoanTerm),
                                                originalAmortTerm(originalAmortTerm),
                                                originalIOTerm(originalIOTerm),
                                                currentLoanAge(currentLoanAge),
                                                grossCoupon(grossCoupon),
                                                feeStrip(feeStrip),
                                                paymentFrequency(paymentFrequency)
{
    if (periodicDebtService)
    {
        this->periodicAmortizingDebtService = periodicDebtService.value();;
    }
    else
    {
        double periodicGrossCoupon = grossCoupon * paymentFrequency / 12.0;
        this->periodicAmortizingDebtService = Utilities::calculatePayment(originalBalance, originalAmortTerm, periodicGrossCoupon);
    }
     

    // TODO: Tokenize and parse the prepayment string, e.g. 'L(30) 5%(24) 4%(24) 3%(12) 2%(12) 1%(12) O(6)'
    if (originalPrepaymentString == "L(30) 5%(24) 4%(24) 3%(12) 2%(12) 1%(12) O(6)")
    {
        original_prepayment_provisions.push_back(Lockout(30));
        original_prepayment_provisions.push_back(FixedPenalty(24, 0.05));
        original_prepayment_provisions.push_back(FixedPenalty(24, 0.04));
        original_prepayment_provisions.push_back(FixedPenalty(12, 0.03));
        original_prepayment_provisions.push_back(FixedPenalty(12, 0.02));
        original_prepayment_provisions.push_back(FixedPenalty(12, 0.01));
        original_prepayment_provisions.push_back(Open(6));
    }
    else
    {
        throw std::invalid_argument("Custom prepayment strings are not yet supported");
    }
}

double Loan::netCoupon()
{
    return grossCoupon - feeStrip;
}
