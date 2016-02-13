
#include "ScanCriteria.hpp"



namespace Xeth{

ScanCriteria::ScanCriteria() : 
    QObject(),
    _interrupted(false)
{
    qRegisterMetaType<Xeth::PartialScanResult>("Xeth::PartialScanResult");
}

ScanCriteria::ScanCriteria(const ScanCriteria &) : QObject()
{}

ScanCriteria::~ScanCriteria()
{
    clear();
}

void ScanCriteria::processBlock(size_t blockIndex, Ethereum::Connector::Block &block, Container::iterator end, ScanResult &result)
{
    static BigInt blockReward("5000000000000000000");
    size_t prevTxSize = result.transactions.size();
    size_t prevStSize = result.stealthPayments.size();

    std::string miner = block.getMiner();
    std::string blockHash = block.getHash();
    time_t blockTime = block.getTimestamp();

    for(Container::iterator it=_criteria.begin(); it!=end; ++it)
    {
        it->second->processHeader(blockIndex, blockHash, miner, blockReward, blockTime, result);
    }

    TransactionCollection transactions = block.getTransactions();

    for(TransactionCollection::Iterator tIt=transactions.begin(), tEnd=transactions.end(); tIt!=tEnd; ++tIt)
    {
        std::string sender = tIt->getSender();
        std::string receiver = tIt->getReceiver();
        std::string txid = tIt->getHash();
        BigInt amount = tIt->getAmount();
        std::string data = tIt->getInput();

        for(Container::iterator it=_criteria.begin(); it!=end; ++it)
        {
            it->second->processTransaction(txid, sender, receiver, amount, data, blockTime, result);
        }
    }

    size_t txSize = result.transactions.size();
    size_t stSize = result.stealthPayments.size();
    if(prevTxSize != txSize || stSize != prevStSize)
    {
        PartialScanResult event = MakePartialScanResult(result, txSize - prevTxSize, stSize - prevStSize, blockIndex);
        emit Data(event);
    }
}

size_t ScanCriteria::size() const
{
    return _criteria.size();
}

void ScanCriteria::clear()
{
    for(Container::iterator it=_criteria.begin(), end=_criteria.end(); it!=end; ++it)
    {
        delete it->second;
    }
    _criteria.clear();
}

ScanCriteria::Iterator ScanCriteria::begin() const
{
    return Iterator(_criteria.begin());
}

ScanCriteria::Iterator ScanCriteria::end() const
{
    return Iterator(_criteria.end());
}


void ScanCriteria::addCriterion(size_t minBlock, ScanCriterion *criterion)
{

    Container::iterator it = std::lower_bound(_criteria.begin(), _criteria.end(), minBlock, CriterionCompare());
    if(it==_criteria.end())
    {
        _criteria.push_front(std::make_pair(minBlock, criterion));
    }
    else
    {
        _criteria.insert(it, std::make_pair(minBlock, criterion));
    }
}


size_t ScanCriteria::parse(BlockChain &blockchain, ScanResult &result)
{
    DummyScanProgress progress;
    return parse(blockchain, result, progress);
}




bool ScanCriteria::CriterionCompare::operator ()(const std::pair<size_t, ScanCriterion *> &criterion, size_t minBlock)
{
    return minBlock < criterion.first;
}


ScanCriteria::Iterator::Iterator() : iterator_adaptor_() {}

ScanCriteria::Iterator::Iterator(const iterator_adaptor_::base_type & p) :
    iterator_adaptor_(p) {}

const ScanCriterion & ScanCriteria::Iterator::dereference() const
{
    return *this->base()->second;
}




}
