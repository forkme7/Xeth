#include "WalletFacade.hpp"
#include <QDebug>


namespace Xeth{

WalletFacade::WalletFacade
(
    const Settings &settings, 
    Ethereum::Connector::Provider &provider, 
    DataBase &database, 
    Notifier &notifier, 
    Synchronizer &synchronizer
) :
    _settings(settings),
    _invoker(notifier),
    _provider(provider),
    _database(database),
    _synchronizer(synchronizer)
{}

QVariant WalletFacade::getAccounts()
{
    GetAccountsCommand command(_provider, _database);
    return _invoker.invoke(command, NullCommandArguments());
}

QVariant WalletFacade::getBalance(const QString &address)
{
    GetBalanceCommand command(_provider);
    return _invoker.invoke(command, address);
}

QVariant WalletFacade::getPendingBalance(const QString &address)
{
    GetPendingBalanceCommand command(_provider);
    return _invoker.invoke(command, address);
}

QVariant WalletFacade::send(const QVariantMap &request)
{
    SendCommand command(_provider, _database);
    return _invoker.invoke(command, request);
}

QVariant WalletFacade::sendToAddress(const QVariantMap &request)
{
    SendToAddressCommand command(_provider, _database);
    return _invoker.invoke(command, request);
}

QVariant WalletFacade::sendToStealth(const QVariantMap &request)
{
    SendToStealthCommand command(_provider, _database);
    return _invoker.invoke(command, request);
}

QVariant WalletFacade::listTransactions(const QVariantMap &request)
{
    ListTransactionsCommand command(_database);
    return _invoker.invoke(command, request);
}


QVariant WalletFacade::importKey(const QVariantMap &request)
{
    ImportKeyCommand command(_settings, _database, _synchronizer);
    return _invoker.invoke(command, request);
}

QVariant WalletFacade::importPresaleKey(const QVariantMap &request)
{
    ImportPresaleKeyCommand command(_settings, _synchronizer);
    return _invoker.invoke(command, request);
}

QVariant WalletFacade::importEthereumKey(const QVariantMap &request)
{
    ImportEthereumKeyCommand command(_database, _synchronizer);
    return _invoker.invoke(command, request);
}

QVariant WalletFacade::importStealthKey(const QVariantMap &request)
{
    ImportStealthKeyCommand command(_database, _synchronizer);
    return _invoker.invoke(command, request);
}

QVariant WalletFacade::exportKey(const QVariantMap &request)
{
    ExportKeyCommand command(_database);
    return _invoker.invoke(command, request);
}

QVariant WalletFacade::exportEthereumKey(const QVariantMap &request)
{
    ExportEthereumKeyCommand command(_database);
    return _invoker.invoke(command, request);
}


QVariant WalletFacade::exportStealthKey(const QVariantMap &request)
{
    ExportStealthKeyCommand command(_database);
    return _invoker.invoke(command, request);
}


QVariant WalletFacade::generateEthereumKey(const QVariantMap &request)
{
    GenerateEthereumKeyCommand command(_database, _synchronizer);
    return _invoker.invoke(command, request);
}


QVariant WalletFacade::generateKey(const QVariantMap &request)
{
    GenerateKeyCommand command(_database, _synchronizer);
    return _invoker.invoke(command, request);
}


QVariant WalletFacade::generateStealthKey(const QVariantMap &request)
{
    GenerateStealthKeyCommand command(_database, _synchronizer);
    return _invoker.invoke(command, request);
}

QVariant WalletFacade::validateAddress(const QString &request)
{
    ValidateAddressCommand command;
    return _invoker.invoke(command, request);
}

QVariant WalletFacade::validateStealthAddress(const QString &request)
{
    ValidateStealthAddressCommand command;
    return _invoker.invoke(command, request);
}


QVariant WalletFacade::changeEthereumKeyPassword(const QVariantMap &request)
{
    ChangeEthereumKeyPasswordCommand command(_database);
    return _invoker.invoke(command, request);
}


QVariant WalletFacade::changeStealthKeyPassword(const QVariantMap &request)
{
    ChangeStealthKeyPasswordCommand command(_database);
    return _invoker.invoke(command, request);
}

QVariant WalletFacade::changePassword(const QVariantMap &request)
{
    ChangeKeyPasswordCommand command(_database);
    return _invoker.invoke(command, request);
}


QVariant WalletFacade::estimateFee(const QVariantMap &request)
{
    EstimateFeeCommand command(_provider);
    return _invoker.invoke(command, request);
}


}
