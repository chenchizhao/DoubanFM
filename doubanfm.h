#ifndef DOUBANFM_H
#define DOUBANFM_H

#include <QDialog>
#include "ui_doubanfmdialog.h"
#include <QNetworkAccessManager>
#include <QList>
#include "douban_types.h"
#include <QProcess>
#include <phonon/mediaobject.h>
#include <QComboBox>

static const int DOUBAN_MANAGER_NUMBER = 9;
static const QString DOUBAN_FM_API_CHANNEL = "http://www.douban.com/j/app/radio/channels";
static const QString DOUBAN_FM_API_ADDR = "http://www.douban.com/j/app/radio/people";
//static const int PLAYLIST_LENGTH = 5;

class DoubanFM : public QDialog
{
    Q_OBJECT
    public:
        explicit DoubanFM( QWidget *parent = NULL );
        ~DoubanFM();
        void getChannels();
        void getNewPlayList( const qint32 &channel, qint32 kbps = 64 );
    private slots:
        void favoriteButtonClicked();
        void forgetButtonClicked();
        void nextButtonClicked();
        void onReceivedChannels( QNetworkReply * );
        void onReceivedNewList( QNetworkReply * );
        void playSong();
        void updateAlbumCover( QNetworkReply * );
        void switchChannel( int );
        void nextSong(const Phonon::MediaSource&);
    private:
        Ui::DoubanFMDialog ui;
        /*
         * @brief m_managers
         *
         * 0: User Relogin
         * 1: new list
         * 2: rate song/unrate song
         * 3: skip song
         * 4: current end
         * 5: bye song
         * 6: get channels
         * 7: playing list
         * 8: Login/Logout
         */
        QNetworkAccessManager *m_managers[DOUBAN_MANAGER_NUMBER];
        QNetworkAccessManager *m_pictManager;
        QList<DoubanChannel> m_channels;
        QList<DoubanFMSong> m_songs;

        int m_channelIndex;
        int m_songIndex;
        DoubanUser *m_user;
        QProcess *m_process;
        Phonon::MediaObject *m_player;

        bool m_isNextButtonClicked;
        bool m_noSongPlaying;
        int m_playListLength;
        bool m_nextSongReady;
};

#endif
