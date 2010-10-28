// playermanager.h
// Created 6/1/2010 by RJ Ryan (rryan@mit.edu)

#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <QList>

#include "configobject.h"
#include "trackinfoobject.h"

class ControlObject;
class Deck;
class Sampler;
class BaseTrackPlayer;

class Library;
class EngineMaster;
class AnalyserQueue;

class PlayerManager : public QObject {
    Q_OBJECT
  public:
    PlayerManager(ConfigObject<ConfigValue> *pConfig,
                  EngineMaster* pEngine,
                  Library* pLibrary,
                  AnalyserQueue* pAnalyserQueue);
    virtual ~PlayerManager();

    // Add a deck to the PlayerManager
    Deck* addDeck();

    // Add a sampler to the PlayerManager
    Sampler* addSampler();

    // Return the number of players
    int numDecks();

    // Return the number of samplers
    int numSamplers();

    // Get a BaseTrackPlayer (i.e. a Deck or a Sampler) by its group
    BaseTrackPlayer* getPlayer(QString group);

    // Get the deck by its deck number. Decks are numbered starting with 1.
    Deck* getDeck(unsigned int player);

    // Get the sampler by its number. Samplers are numbered starting with 1.
    Sampler* getSampler(unsigned int sampler);

  public slots:
    // Slots for loading tracks into a Player, which is either a Sampler or a Deck
    void slotLoadTrackToPlayer(TrackPointer pTrack, QString group);
    void slotLoadToPlayer(QString location, QString group);

    // Slots for loading tracks to decks
    void slotLoadTrackIntoNextAvailableDeck(TrackPointer pTrack);
    void slotLoadToDeck(QString location, int deckNumber);

    // Slots for loading tracks to samplers
    void slotLoadTrackIntoNextAvailableSampler(TrackPointer pTrack);
    void slotLoadToSampler(QString location, int samplerNumber);

  private:
    TrackPointer lookupTrack(QString location);
    ConfigObject<ConfigValue>* m_pConfig;
    EngineMaster* m_pEngine;
    Library* m_pLibrary;
    AnalyserQueue* m_pAnalyserQueue;
    ControlObject* m_pCONumDecks;
    ControlObject* m_pCONumSamplers;

    QList<Deck*> m_decks;
    QList<Sampler*> m_samplers;
    QMap<QString, BaseTrackPlayer*> m_players;
};

#endif /* PLAYERMANAGER_H */
