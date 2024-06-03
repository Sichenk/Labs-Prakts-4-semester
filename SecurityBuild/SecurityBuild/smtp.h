#ifndef BUILDINGSSECURITY_SMTP_H
#define BUILDINGSSECURITY_SMTP_H

#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslSocket>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include <QByteArray>

class Smtp : public QObject {
    Q_OBJECT

private:
    int timeout;
    QString message;
    QTextStream *t;
    QSslSocket *socket;
    QString from;
    QString rcpt;
    QString response;
    QString user;
    QString pass;
    QString host;
    int port;
    enum states{Tls,HandShake,Auth,User,Pass,Rcpt,Mail,Data,Init,Body,Quit,Close};
    int state;

public:
    Smtp(const QString &user, const QString &pass, const QString &host = "smtp.gmail.com", int port = 465, int timeout = 30000 ) {
        socket = new QSslSocket(this);
        connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

        this->user = user;
        this->pass = pass;

        this->host = host;
        this->port = port;
        this->timeout = timeout;
    }

    ~Smtp() {
        delete t;
        delete socket;
    }

    void sendMail(const QString &from, const QString &to, const QString &subject, const QString &body) {
        message = "To: " + to + "\n";
        message.append("From: " + from + "\n");
        message.append("Subject: " + subject + "\n");
        message.append(body);
        message.replace( QString::fromLatin1( "\n" ), QString::fromLatin1( "\r\n" ) );
        message.replace( QString::fromLatin1( "\r\n.\r\n" ),
                        QString::fromLatin1( "\r\n..\r\n" ) );
        this->from = from;
        rcpt = to;
        state = Init;
        socket->connectToHostEncrypted(host, port); //"smtp.gmail.com" and 465 for gmail TLS
        if (!socket->waitForConnected(timeout)) {
            qDebug() << socket->errorString();
        }

        t = new QTextStream( socket );
    }

signals:
    void status( const QString &);

private slots:
    void readyRead() {
        qDebug() << "readyRead";
        QString responseLine;
        do {
            responseLine = socket->readLine();
            response += responseLine;
        }
        while ( socket->canReadLine() && responseLine[3] != ' ' );

        responseLine.truncate( 3 );

        qDebug() << "Server response code:" <<  responseLine;
        qDebug() << "Server response: " << response;

        if ( state == Init && responseLine == "220" ) {
            *t << "EHLO localhost" <<"\r\n";
            t->flush();

            state = HandShake;
        }
        else if (state == HandShake && responseLine == "250") {
            socket->startClientEncryption();
            if(!socket->waitForEncrypted(timeout))
            {
                qDebug() << socket->errorString();
                state = Close;
            }
            *t << "EHLO localhost" << "\r\n";
            t->flush();
            state = Auth;
        }
        else if (state == Auth && responseLine == "250") {
            qDebug() << "Auth";
            *t << "AUTH LOGIN" << "\r\n";
            t->flush();
            state = User;
        }
        else if (state == User && responseLine == "334") {
            qDebug() << "Username";
            *t << user.toUtf8().toBase64() << "\r\n";
            t->flush();

            state = Pass;
        }
        else if (state == Pass && responseLine == "334") {
            qDebug() << "Pass";
            *t << pass.toUtf8().toBase64() << "\r\n";
            t->flush();

            state = Mail;
        }
        else if ( state == Mail && responseLine == "235" ) {
            qDebug() << "MAIL FROM:<" << from << ">";
            *t << "MAIL FROM:<" << from << ">\r\n";
            t->flush();
            state = Rcpt;
        }
        else if ( state == Rcpt && responseLine == "250" ) {
            *t << "RCPT TO:<" << rcpt << ">\r\n"; //r
            t->flush();
            state = Data;
        }
        else if ( state == Data && responseLine == "250" ) {
            *t << "DATA\r\n";
            t->flush();
            state = Body;
        }
        else if ( state == Body && responseLine == "354" ) {
            *t << message << "\r\n.\r\n";
            t->flush();
            state = Quit;
        }
        else if (state == Quit && (responseLine == "250" || responseLine == "221")) { // Обрабатываем как "250" так и "221"
            *t << "QUIT\r\n";
            t->flush();
            //state = Close;
            //emit status(tr("Code sent"));
        }
        else if (state == Close) {
            //emit status(tr("Failed to send message"));
            deleteLater();
        }
        else {
            QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Unexpected reply from SMTP server:\n\n" ) + response );
            state = Close;
            emit status( tr( "Failed to send message" ) );
        }
        response = "";
    }

};
#endif
