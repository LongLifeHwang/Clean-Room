#include <wiringPi.h>
#include <stdio.h>

#define DUST_SENSOR_PIN 0 // 아날로그 출력 핀

void setup()
{
    wiringPiSetup(); // wiringPi 초기화
    pinMode(DUST_SENSOR_PIN, INPUT); // 아날로그 입력으로 설정
}

int readDustLevel()
{
    int dustLevel = analogRead(DUST_SENSOR_PIN); // 아날로그 입력값 읽기
    return dustLevel;
}

int main(void) {
    setup(); // 초기화

    while (1) {
        int dustLevel = readDustLevel(); // 미세먼지 농도 측정

        // 미세먼지 농도 출력
        printf("미세먼지 농도: %d\n", dustLevel);

        delay(1000); // 1초 대기 후 다시 측정
    }

    return 0;
}