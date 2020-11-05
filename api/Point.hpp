#ifndef BATTLESHIP_POINT_HPP
#define BATTLESHIP_POINT_HPP

class Point {
public:
    enum Letter {
        A = 0,
        B = 1,
        C = 2,
        D = 3,
        E = 4,
        F = 5,
        G = 6,
        H = 7,
        I = 8,
        J = 9
    };

    enum Number {
        ZERO  = 0,
        ONE   = 1,
        TWO   = 2,
        THREE = 3,
        FOUR  = 4,
        FIVE  = 5,
        SIX   = 6,
        SEVEN = 7,
        EIGHT = 8,
        NINE  = 9
    };

    Point(Letter letter, Number number);

    Letter letter;
    Number number;

    static bool isXCoordinate(int charcode);
    static bool isYCoordinate(int charcode);
};

#endif //BATTLESHIP_POINT_HPP
