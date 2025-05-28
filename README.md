# ROBO CAR PROJECT

## How to build

```sh
$ git clone https://github.com/yarik64/${PROJECT_NAME}.git
$ cd ${PROJECT_NAME}
$ git submodule update --init --recursive
$ make build
```

### build in docker
```sh
$ docker build -t robocar .
$ docker cp robocat:build/pwm_sg90.uf2 .
```

## UART commands
Car recieve commands over UART (pins RX:0 TX:1)
single command must have a 2 chars, looks like this:

```
s100
r15
```

this mean:
```
s - speed 
r - rule
```

second char must have value in interval 0-255

```
s0 (speed = 0)
r 10 (rule to 10. Rule need to calibrated)
```
