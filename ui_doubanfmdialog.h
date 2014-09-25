/********************************************************************************
** Form generated from reading UI file 'doubanfmdialog.ui'
**
** Created: Thu Sep 25 10:25:39 2014
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOUBANFMDIALOG_H
#define UI_DOUBANFMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DoubanFMDialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *nameLabel;
    QSpacerItem *horizontalSpacer_2;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *albumLabel;
    QVBoxLayout *verticalLayout;
    QComboBox *channelBox;
    QSpacerItem *verticalSpacer;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout;
    QPushButton *favoriteButton;
    QPushButton *forgetButton;
    QPushButton *nextButton;

    void setupUi(QDialog *DoubanFMDialog)
    {
        if (DoubanFMDialog->objectName().isEmpty())
            DoubanFMDialog->setObjectName(QString::fromUtf8("DoubanFMDialog"));
        DoubanFMDialog->resize(438, 410);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DoubanFMDialog->sizePolicy().hasHeightForWidth());
        DoubanFMDialog->setSizePolicy(sizePolicy);
        layoutWidget = new QWidget(DoubanFMDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 411, 50));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(28, 48, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        nameLabel = new QLabel(layoutWidget);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(7);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(nameLabel->sizePolicy().hasHeightForWidth());
        nameLabel->setSizePolicy(sizePolicy1);
        nameLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(nameLabel);

        horizontalSpacer_2 = new QSpacerItem(28, 48, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        layoutWidget1 = new QWidget(DoubanFMDialog);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 70, 411, 221));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        albumLabel = new QLabel(layoutWidget1);
        albumLabel->setObjectName(QString::fromUtf8("albumLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(5);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(albumLabel->sizePolicy().hasHeightForWidth());
        albumLabel->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(albumLabel);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        channelBox = new QComboBox(layoutWidget1);
        channelBox->setObjectName(QString::fromUtf8("channelBox"));

        verticalLayout->addWidget(channelBox);

        verticalSpacer = new QSpacerItem(20, 88, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_3->addLayout(verticalLayout);

        layoutWidget2 = new QWidget(DoubanFMDialog);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 310, 411, 81));
        horizontalLayout = new QHBoxLayout(layoutWidget2);
        horizontalLayout->setSpacing(50);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        favoriteButton = new QPushButton(layoutWidget2);
        favoriteButton->setObjectName(QString::fromUtf8("favoriteButton"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(favoriteButton->sizePolicy().hasHeightForWidth());
        favoriteButton->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(favoriteButton);

        forgetButton = new QPushButton(layoutWidget2);
        forgetButton->setObjectName(QString::fromUtf8("forgetButton"));
        sizePolicy3.setHeightForWidth(forgetButton->sizePolicy().hasHeightForWidth());
        forgetButton->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(forgetButton);

        nextButton = new QPushButton(layoutWidget2);
        nextButton->setObjectName(QString::fromUtf8("nextButton"));
        sizePolicy3.setHeightForWidth(nextButton->sizePolicy().hasHeightForWidth());
        nextButton->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(nextButton);


        retranslateUi(DoubanFMDialog);

        QMetaObject::connectSlotsByName(DoubanFMDialog);
    } // setupUi

    void retranslateUi(QDialog *DoubanFMDialog)
    {
        DoubanFMDialog->setWindowTitle(QApplication::translate("DoubanFMDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        nameLabel->setText(QApplication::translate("DoubanFMDialog", "No name", 0, QApplication::UnicodeUTF8));
        albumLabel->setText(QApplication::translate("DoubanFMDialog", "No album", 0, QApplication::UnicodeUTF8));
        channelBox->clear();
        channelBox->insertItems(0, QStringList()
         << QApplication::translate("DoubanFMDialog", "a", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DoubanFMDialog", "b", 0, QApplication::UnicodeUTF8)
        );
        favoriteButton->setText(QApplication::translate("DoubanFMDialog", "\345\226\234\346\254\242", 0, QApplication::UnicodeUTF8));
        forgetButton->setText(QApplication::translate("DoubanFMDialog", "\351\201\227\345\277\230", 0, QApplication::UnicodeUTF8));
        nextButton->setText(QApplication::translate("DoubanFMDialog", "\344\270\213\344\270\200\351\246\226", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DoubanFMDialog: public Ui_DoubanFMDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOUBANFMDIALOG_H
