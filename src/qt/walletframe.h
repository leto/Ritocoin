// Copyright (c) 2013-2018 The Bitcoin Core developers
// Copyright (c) 2017 The Raven Core developers
// Copyright (c) 2018 The Rito Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef RITO_QT_WALLETFRAME_H
#define RITO_QT_WALLETFRAME_H

#include <QFrame>
#include <QMap>

class RitoGUI;
class ClientModel;
class PlatformStyle;
class SendCoinsRecipient;
class WalletModel;
class WalletView;

QT_BEGIN_NAMESPACE
class QStackedWidget;
QT_END_NAMESPACE

/**
 * A container for embedding all wallet-related
 * controls into RitoGUI. The purpose of this class is to allow future
 * refinements of the wallet controls with minimal need for further
 * modifications to RitoGUI, thus greatly simplifying merges while
 * reducing the risk of breaking top-level stuff.
 */
class WalletFrame : public QFrame
{
    Q_OBJECT

public:
    explicit WalletFrame(const PlatformStyle *platformStyle, RitoGUI *_gui = 0);
    ~WalletFrame();

    void setClientModel(ClientModel *clientModel);

    bool addWallet(const QString& name, WalletModel *walletModel);
    bool setCurrentWallet(const QString& name);
    bool removeWallet(const QString &name);
    void removeAllWallets();

    bool handlePaymentRequest(const SendCoinsRecipient& recipient);

    void showOutOfSyncWarning(bool fShow);

Q_SIGNALS:
    /** Notify that the user has requested more information about the out-of-sync warning */
    void requestedSyncWarningInfo();

private:
    QStackedWidget *walletStack;
    RitoGUI *gui;
    ClientModel *clientModel;
    QMap<QString, WalletView*> mapWalletViews;

    bool bOutOfSync;

    const PlatformStyle *platformStyle;

    WalletView *currentWalletView();

public Q_SLOTS:
    /** Switch to overview (home) page */
    void gotoOverviewPage();
    /** Switch to history (transactions) page */
    void gotoHistoryPage();
    /** Switch to receive coins page */
    void gotoReceiveCoinsPage();
    /** Switch to send coins page */
    void gotoSendCoinsPage(QString addr = "");

    /** Show Sign/Verify Message dialog and switch to sign message tab */
    void gotoSignMessageTab(QString addr = "");
    /** Show Sign/Verify Message dialog and switch to verify message tab */
    void gotoVerifyMessageTab(QString addr = "");

    /** Encrypt the wallet */
    void encryptWallet(bool status);
    /** Backup the wallet */
    void backupWallet();
    /** Change encrypted wallet passphrase */
    void changePassphrase();
    /** Ask for passphrase to unlock wallet temporarily */
    void unlockWallet();

    /** Show used sending addresses */
    void usedSendingAddresses();
    /** Show used receiving addresses */
    void usedReceivingAddresses();
    /** Pass on signal over requested out-of-sync-warning information */
    void outOfSyncWarningClicked();

    /** RITO START */

    /** Switch to assets page */
    void gotoAssetsPage();
    void gotoCreateAssetsPage();
    void gotoManageAssetsPage();
    /** RITO END */
};

#endif // RITO_QT_WALLETFRAME_H
