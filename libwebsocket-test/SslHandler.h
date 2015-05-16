/**
    SslHandler.h
    Manage ssl file formatted to QT ssl format cert

    @author Bertrand Martel
    @version 1.0
*/
#ifndef SSLHANDLER_H
#define SSLHANDLER_H
#include "QSslCertificate"
#include "QList"
#include "QSslKey"

/**
 * @brief The SslHandler class
 *      format ssl file cert to QT format
 */
class SslHandler
{
public:

    /**
     * @brief retrieveveCertFromFile
     *      retrieve ssl certificate type file
     * @param filename
     *      certificate file name (should be in pem format)
     * @return
     *      QSslcertificate format
     */
    static QSslCertificate retrieveCertFromFile(char * filename);


    static QSslKey retrieveKeyCertFile(char * filename,char * certPass);


    /**
     * @brief retrieveveCaCertListFromFile
     *      retrieve list of certification authorityto be used in server
     * @param filename
     *      certificates file name (should be in pem format)
     * @return
     *      QList< QSslCertificate > format
     */
    static QList< QSslCertificate > retrieveveCaCertListFromFile(char * filename);
};

#endif // SSLHANDLER_H
