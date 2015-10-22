#ifndef BEEPER_H
#define BEEPER_H

/**
 * @brief The Beeper class : controls the beep. Starts it to play a frequency until you stop it.
 */
class Beeper
{
public:

    /**
     * @brief Get the beeper object
     * @return the instancied object
     */
    static Beeper& get(){
      static Beeper instance;
      return instance;
    }

    /**
     * @brief Stops the beeper if used, then plays the given frequency
     * @param frequency the frequency to play
     */
    void startBeep(float frequency);

    /**
     * @brief Stops the beeper only if the current frequency is being played
     * @param frequency the frequency to stop
     */
    void stopBeep(float frequency);

    /**
     * @brief Stops the beeper whatever the current frequency
     */
    void stopBeep();




private:
    /**
     * @brief Private : constructs the beeper class
     */
    Beeper();

    bool _isBeeping;
    float _currentFrequency; //Current frequency

    int _consoleFd = -1; //used for the beeper
};

#endif // BEEPER_H
