# Skilled_Eagle

## ClassDiagram

![Alt text](http://g.gravizo.com/g?
  digraph G {@startuml
             class IrReceiver{
             -dataToSend
             +receive()
             }
             class IrSender{
             -receivedData
             +receive()
             -decode()
             }
             class Display_controller {
             +test()
             +push(data)
             }
             class Sound_Controller{
             +start(sound, duration)
             }
             class Wifi_Controller{

             }
             class Fire{
             -getButton()
             }
             class Console{
             }
             class Data_Controller{
             -score
             -lives
             -wapen
             -gameMode
             +addScore(score)
             +setLives(lives)
             +lowerLive()
             +setWapen(wapen)
             +getWapen()
             +setGameMode()
             +getGameMode()
             }

             enum Wapens
             enum GameModes


             Console <.. Data_Controller: <include>
             Wifi_Controller <.. Data_Controller: <include>
             Display_controller <.. Data_Controller: <include>
             IrReceiver <.. Data_Controller: <include>
             Fire <.. Data_Controller: <include>
             Wapens <.. Data_Controller: <include>
             GameModes <.. Data_Controller: <include>
             Sound_Controller <|-- Fire
             IrSender <|-- Fire

             @enduml
  }
)