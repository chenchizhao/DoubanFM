#include "doubanfm.h"
#include <qjson/parser.h>
#include "utils.hpp"
#include "douban_types.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <iostream>
#include <algorithm>
#include <QDebug>

DoubanFM::DoubanFM( QWidget *parent ) : QDialog( parent )
{
    ui.setupUi( this );
    connect( ui.favoriteButton, SIGNAL(clicked()),
             this, SLOT(favoriteButtonClicked()) );
    connect( ui.forgetButton, SIGNAL(clicked()),
             this, SLOT(forgetButtonClicked()) );
    connect( ui.nextButton, SIGNAL(clicked()),
             this, SLOT(nextButtonClicked()) );

    for( int i = 0; i < DOUBAN_MANAGER_NUMBER; ++i ) {
        m_managers[i] = 0;
    }

    getChannels();
    m_currIndex = 0;
    m_user = 0;
    m_process = 0;
    m_player = Phonon::createPlayer( Phonon::MusicCategory, Phonon::MediaSource("") );
}

DoubanFM::~DoubanFM()
{
    
}

void DoubanFM::getChannels()
{
    if( m_managers[6] == 0 ) {
        m_managers[6] = new QNetworkAccessManager( this );
        connect( m_managers[6], SIGNAL(finished(QNetworkReply *)),
                 this, SLOT(onReceivedChannels(QNetworkReply *)) );
    }

    m_managers[6]->get( QNetworkRequest(QUrl(DOUBAN_FM_API_CHANNEL)) );
}

void DoubanFM::onReceivedChannels( QNetworkReply *reply )
{
    //QTextCodec *codec = QTextCodec::codecForName( "utf-8" );
    //QString all = codec->toUnicode( reply->readAll() );
    QJson::Parser parser;
    bool ok;

    QByteArray json = reply->readAll();
    QVariant result = parser.parse( json, &ok );

    if( !ok ) {
        qFatal( "onReceivedChannels: an error occured during parsing" );
        exit(1);
    }

    QVariantMap obj = result.toMap();
    QVariantList chList = obj["channels"].toList();
    foreach( const QVariant& item, chList ) {
        QVariantMap ch = item.toMap();
        DoubanChannel dc;
        dc.name = ch["name"].toString();
        dc.name_en = ch["name_en"].toString();
        dc.seq_id = ch["seq_id"].toInt();
        dc.channel_id = ch["channel_id"].toInt();
        dc.abbr_en = ch["abbr_en"].toString();
        m_channels.append(dc);
    }

    std::sort( m_channels.begin(), m_channels.end(),
            compareChannels );

    foreach( const DoubanChannel &dc, m_channels ) {
        qDebug() << dc.name;
    }

    reply->deleteLater();

    qint32 channel = m_channels[m_currIndex].channel_id;
    getNewPlayList( channel );
}

void DoubanFM::getNewPlayList( const qint32 &channel, qint32 kbps )
{
    QString args = QString( "?app_name=radio_desktop_win&version=100" )
        + QString("&user_id=") + ( (m_user) ? m_user->user_id : QString() )
        + QString("&expire=") + ( (m_user) ? m_user->expire : QString() )
        + QString("&token=") + ( (m_user) ? m_user->token : QString() )
        + QString("&sid=&h=")
        + QString("&channel=") + QString::number( channel, 10 )
        + QString("&kbps=") + QString::number( kbps, 10 )
        + QString("&type=n");
    if( m_managers[1] == 0 ) {
        m_managers[1] = new QNetworkAccessManager( this );
        connect( m_managers[1], SIGNAL(finished(QNetworkReply *)),
                this, SLOT(onReceivedNewList(QNetworkReply *)) );
    }
    m_managers[1]->get( QNetworkRequest(QUrl(DOUBAN_FM_API_ADDR + args)) );
}

void DoubanFM::onReceivedNewList( QNetworkReply *reply )
{
    //QTextCodec *codec = QTextCodec::codecForName( "utf-8" );
    //QString all = codec->toUnicode( reply->readAll() );
    QJson::Parser parser;
    QList<DoubanFMSong> songs;
    bool ok;
    QByteArray json = reply->readAll();
    QVariant result = parser.parse( json, &ok );

    if( !ok ) {
        qFatal( "onReceivedNewList: an error occured during parsing" );
        exit(1);
    }

    QVariantMap obj = result.toMap();
    if( obj["r"].toInt() != 0 ) {
        if( obj["err"].toString() == "expired" ) {
            qDebug() << Q_FUNC_INFO << "User expired.Relogin";
            //userRelogin();
        }
    }

    QVariantList songList = obj["song"].toList();
    foreach( const QVariant& item, songList ) {
        QVariantMap song = item.toMap();
        DoubanFMSong s;
        s.album = song["album"].toString();
        s.picture = song["picture"].toString();
        s.ssid = song["ssid"].toString();
        s.artist = song["artist"].toString();
        s.url = song["url"].toString();
        s.company = song["company"].toString();
        s.title = song["title"].toString();
        s.public_time = song["public_time"].toString();
        s.sid = song["sid"].toUInt();
        s.aid = song["aid"].toUInt();
        s.albumtitle = song["albumtitle"].toString();
        s.like = song["like"].toBool();
        songs.push_back(s);
        qDebug() << s.url;
    }

    //emit receivedNewList(songs);
    reply->deleteLater();
    play( songs );
}

void DoubanFM::play( const QList<DoubanFMSong>& rcvsongs )
{
    QString url;
    foreach( const DoubanFMSong &song, rcvsongs )    
    {
        url = song.url;
        m_player->setCurrentSource( Phonon::MediaSource(url) );
        m_player->play();
    }
}

void DoubanFM::favoriteButtonClicked()
{

}

void DoubanFM::forgetButtonClicked()
{

}

void DoubanFM::nextButtonClicked()
{

}
