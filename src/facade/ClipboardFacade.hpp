#pragma once 

#include <QObject>
#include <QVariant>
#include <QVariantMap>
#include <QString>


#include "command/clipboard/CopyToClipboardCommand.hpp"
#include "command/clipboard/GetFromClipboardCommand.hpp"

#include "Notifier.hpp"
#include "Invoker.hpp"


namespace Xeth{


class ClipboardFacade : public QObject
{
    Q_OBJECT

    public:

        ClipboardFacade(Notifier &);

        Q_INVOKABLE QVariant get();
        Q_INVOKABLE QVariant set(const QString &);

    private:
        Invoker _invoker;
};


}