#include "doubanfm.h"
#include <qjson/parser.h>
#include "utils.hpp"
#include "douban_types.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <iostream>
#include <algorithm>
#include <QDebug>
#include <unistd.h>

DoubanFM::DoubanFM( QWidget *parent ) : QDialog( parent )
{
    m_channelIndex = 0;
    m_songIndex = 0;
    m_user = 0;
    m_process = 0;
    m_player = Phonon::createPlayer( Phonon::MusicCategory, Phonon::MediaSource("") );
    m_isNextButtonClicked = false;
    m_pictManager = new QNetworkAccessManager( this );
    m_noSongPlaying = true;
    m_playListLength = 0;

    ui.setupUi( this );
    connect( ui.favoriteButton, SIGNAL(clicked()),
             this, SLOT(favoriteButtonClicked()) );
    connect( ui.forgetButton, SIGNAL(clicked()),
             this, SLOT(forgetButtonClicked()) );
    connect( ui.nextButton, SIGNAL(clicked()),
             this, SLOT(nextButtonClicked()) );
    connect( m_player, SIGNAL(currentSourceChanged(const Phonon::MediaSource &)),
             this, SLOT(nextSong(const Phonon::MediaSource&)) );
    connect( m_pictManager, SIGNAL(finished(QNetworkReply *)),
             this, SLOT(updateAlbumCover(QNetworkReply *)) );
    connect( ui.channelBox, SIGNAL(currentIndexChanged(int)),
             this, SLOT(switchChannel(int)) );

    for( int i = 0; i < DOUBAN_MANAGER_NUMBER; ++i ) {
        m_managers[i] = 0;
    }

    ui.nextButton->setEnabled( false );

    ui.favoriteButton->setCheckable( true );
    ui.favoriteButton->setStyleSheet(
            "QPushButton{border-image: url(:/img/unlike.png);}"
            "QPushButton:hover{border-image: url(:/img/like_disabled.png);}"
            "QPushButton:pressed{border-image: url(:/img/like_disabled.png);}"
            "QPushButton:checked{border-image: url(:/img/like.png);}"
            "QPushButton:disabled{border-image: url(:/img/like_disabled.png);}");

    ui.forgetButton->setStyleSheet(
            "QPushButton{border-image: url(:/img/trash_can_normal.png);}"
            "QPushButton:hover{border-image: url(:/img/trash_can_clicked.png);}");

    ui.nextButton->setStyleSheet(
            "QPushButton{border-image: url(:/img/next_normal.png);}"
            "QPushButton:hover{border-image: url(:/img/next_clicked.png);}"
            );

    this->setFixedSize( this->width(), this->height() );

    getChannels();
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
        ui.channelBox->addItem( dc.name );
    }

    std::sort( m_channels.begin(), m_channels.end(),
            compareChannels );

    reply->deleteLater();

    qint32 channel = m_channels[m_channelIndex].channel_id;
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
    m_playListLength = 0;

    QJson::Parser parser;
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

    if( m_songs.size() > 10 )
        for( int i = 0; i < m_songs.size() - 10; i++ )
        {
            m_songs.pop_front();
            --m_songIndex;
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
        m_songs.push_back(s);
        m_playListLength++;
        qDebug() << s.title;
    }

    reply->deleteLater();
    playSong();
    qDebug() << "queue ready";
    ui.nextButton->setEnabled( true );
}

void DoubanFM::playSong()
{
    QString url;

    //qDebug() << "playing index is " << m_songIndex;
    url = m_songs[m_songIndex].url;

    // block the currentSourceChanged signal, in case that
    // function nextSong is called
    bool whetherBlock = m_player->blockSignals( true );
    m_player->enqueue(url);
    m_player->blockSignals( whetherBlock );

    if( m_noSongPlaying )
    {
        m_player->play();
    }

    m_noSongPlaying = false;

    ui.nameLabel->setText( m_songs[m_songIndex].title );

    QString mod_url = m_songs[m_songIndex].picture;
    mod_url.replace( "mpic", "lpic" );

    m_pictManager->get( QNetworkRequest(QUrl(mod_url)) );
}

void DoubanFM::favoriteButtonClicked()
{

}

void DoubanFM::forgetButtonClicked()
{

}

void DoubanFM::nextButtonClicked()
{
    ++m_songIndex;

    if( m_songIndex % m_songs.length() == m_songs.length()-1 )
    {
        ui.nextButton->setEnabled( false );
        getNewPlayList( m_channels[m_channelIndex].channel_id );
    }

    // block the currentSourceChanged signal, in case that
    // function nextSong is called
    bool whetherBlock = m_player->blockSignals( true );
    m_player->enqueue(m_songs[m_songIndex].url);
    m_player->setCurrentSource( Phonon::MediaSource(m_songs[m_songIndex].url) );
    m_player->play();
    m_player->blockSignals( whetherBlock );

    ui.nameLabel->setText( m_songs[m_songIndex].title );
    QString mod_url = m_songs[m_songIndex].picture;
    mod_url.replace( "mpic", "lpic" );

    m_pictManager->get( QNetworkRequest(QUrl(mod_url)) );
}

void DoubanFM::updateAlbumCover( QNetworkReply *reply )
{
    if( reply->error() != QNetworkReply::NoError ) {
        qDebug() << "Error: Album image receive error";
        reply->deleteLater();
        return;
    }

    const QByteArray data(reply->readAll());
    if( !data.size() )
        qDebug() << Q_FUNC_INFO << "received pictures looks like nothing";
    QImage image = QImage::fromData( data );

    int w = ui.albumLabel->width();
    int h = ui.albumLabel->height();

    ui.albumLabel->setPixmap( QPixmap::fromImage(image).scaled(w, h, Qt::KeepAspectRatio) );
}

void DoubanFM::switchChannel( int index )
{
    // when a default channel is selected, a currentIndexChanged signal will be emited
    if( m_noSongPlaying )
        return;

    // block the currentSourceChanged signal, in case that
    // function nextSong is called
    bool whetherBlock = m_player->blockSignals( true );

    m_player->stop();
    m_player->clearQueue();
    m_player->clear();
    m_songs.clear();

    m_noSongPlaying = true; // let m_player->play() called
    m_songIndex = 0;

    m_channelIndex = index;
    getNewPlayList( m_channels[m_channelIndex].channel_id );

    // restore block condition
    m_player->blockSignals( whetherBlock );
}

void DoubanFM::nextSong(const Phonon::MediaSource& ms)
{
    Q_UNUSED( ms );
    nextButtonClicked(); 
}
