# i2c-relays-esp32

Configuração de Relays através de um ESP32 com o uso do Protocolo I2C

Cada address tem dois ports.

- Se o input tiver 8 bits entao é utilizado o 1º port do 1º address

- Se o input tiver 16 bits entao é utilizado o 1º e 2º port do 1º address (8 bits para cada, respetivamente)

- Se o input tiver 24 bits entao é utilizado o é utilizado o 1º e 2º port do 1º address e 1º port do 2º address (8 bits para cada, respetivamente)

- Se o input tiver 32 bits entao é utilizado o 1º e 2º port do 1º address e 1º e 2º port do 2º address (8 bits para cada, respetivamente)

e por ai em diante.
