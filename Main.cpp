#include <iostream>
#include <Chess.h>

int main()
{
    Logger::GetLoggerInstance()->SetLogLevel(LOG_INFO);
    Logger::GetLoggerInstance()->SetLogBitMask(0xf);
    
    Chess chess;
    
    chess.PlayGame();
    return 0;
}
