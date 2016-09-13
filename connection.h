#ifndef CONNECTION_H
#define CONNECTION_H

#include <QAbstractSocket>
#include <functional>

#include "parser.h"


namespace QJSTP
{

class Connection: public QObject
{
    Q_OBJECT

public:
    typedef std::function<void(QScriptValue)> handler;

    static const QByteArray TERMINATOR;

    Connection(QString address, quint16 port, bool useSSL = false);

    void handshake(QString name, QScriptValue parameters, handler callback = NULL);
    void call(QString interface, QString method, QScriptValue parameters, handler callback);
    void callback(quint64 id, QScriptValue parameters);
    void event(QString interface, QString method, QScriptValue parameters, QList <handler> callbacks);
    void inspect(QString interface, handler callback);

    //    void state();
    //    void stream();
    //    void health();

    QAbstractSocket *socket;

private:



    QByteArray buffer;

    QString sessionId;
    quint64 packageId;

    QHash <quint64, QList<handler>> callbacks;

    QHash<QString, QVector<QString>> serverMethods;

    static const QString HANDSHAKE;
    static const QString CALL;
    static const QString CALL_BACK;
    static const QString EVENT;
    static const QString INSPECT;

//    static const QString STATE;
//    static const QString STREAM;
//    static const QString HEALTH;

    void onHandshake(QScriptValue parameters);
    void onCall(QScriptValue parameters);
    void onCallback(QScriptValue parameters);
    void onEvent(QScriptValue parameters);
    void onInspect(QString interface, QScriptValue parameters);


private slots :
    void onConnected();
    void onData();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError socketError);

};

}

#endif // CONNECTION_H
