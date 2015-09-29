/********************************************************************
    Copyright (c) 2013-2015 - Mogara

    This file is part of QSanguosha.

    This game engine is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 3.0
    of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

    See the LICENSE file for more details.

    Mogara
*********************************************************************/

#ifndef ROOMSCENE_H
#define ROOMSCENE_H

#include "structs.h"

#include <QQuickItem>

class Client;
class ClientPlayer;

class RoomScene : public QQuickItem
{
    Q_OBJECT

public:
    RoomScene(QQuickItem *parent = 0);

    //From QML to C++
    Q_INVOKABLE void onChooseGeneralFinished(const QString &head, const QString &deputy);
    Q_INVOKABLE void onCardSelected(const QVariantList &cardIds);
    Q_INVOKABLE void onPhotoSelected(const QVariantList &seats);
    Q_INVOKABLE void onAccepted();
    Q_INVOKABLE void onRejected();
    Q_INVOKABLE void onFinished();

signals:
    //Signals from C++ to QML
    void moveCards(const QVariant &moves);
    void enableCards(const QVariant &cardIds);
    void enablePhotos(const QVariant &seats);
    void chooseGeneral(const QVariant &generals);
    void startEmotion(const QString &emotion, int seat);
    void playAudio(const QString &path);
    void showIndicatorLine(int from, const QVariantList &tos);
    void showPrompt(const QString &prompt);
    void setAcceptEnabled(bool enabled);
    void setRejectEnabled(bool enabled);
    void setFinishEnabled(bool enabled);

private:
    enum RespondingState
    {
        InactiveState,
        UsingCardState,
        RespondingCardState
    };

    void updateButtonState();
    void resetDashboard();
    void enableCards(const QString &pattern);
    void enableCards(const QList<const Card *> &cards);

    void onSeatArranged();
    void onChooseGeneralRequested(const QStringList &candidates);
    void onCardsMoved(const QList<CardsMoveStruct> &moves);
    void onUsingCard(const QString &pattern);
    void onDamageDone(const ClientPlayer *victim, DamageStruct::Nature nature, int damage);
    void onRecoverDone(const ClientPlayer *from, const ClientPlayer *to, int num);
    void onCardUsed(const ClientPlayer *from, const QList<const ClientPlayer *> &tos);
    void onCardAsked(const QString &pattern, const QString &prompt);
    void onCardsAsked(const QString &pattern, const QString &prompt, int minNum, int maxNum, bool optional);

    Client *m_client;
    QList<const Card *> m_selectedCard;
    QList<const Player *> m_selectedPlayer;
    RespondingState m_respondingState;
    int m_minRespondingCardNum;
    int m_maxRespondingCardNum;
    bool m_respondingOptional;
    QString m_respondingPattern;
};

#endif // ROOMSCENE_H
