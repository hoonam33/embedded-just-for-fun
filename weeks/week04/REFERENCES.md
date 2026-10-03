# 4주차 자료 안내

## 학습 기준

- MCU: STM32F030R8
- Board: NUCLEO-F030R8
- Datasheet: [ST DS9773 Rev 5](https://www.st.com/resource/en/datasheet/stm32f030r8.pdf), 2021-11
- 공개 예제: STMicroelectronics/STM32CubeF0, GPIO_IOToggle
- Version: `v1.11.5`
- 고정 Commit: `e220bfb12a162cfbf3bb65663e987e0d6550e9b4`
- 예제 경로: `Projects/STM32F030R8-Nucleo/Examples/GPIO/GPIO_IOToggle/`
- 분석할 Build 설정: `SW4STM32/STM32F030R8-Nucleo/`

Datasheet는 Family 공통 문서입니다. STM32F030R8 열과 STM32F030x8에 해당하는 그림을 사용하세요. 페이지는 PDF에 인쇄된 번호입니다.

| 자료 위치 | 확인할 내용 |
| --- | --- |
| Table 2, p10 | 선택한 부품의 사양 |
| Figure 1, p11 | CPU·Memory·주변장치 연결 |
| §3.1~3.2, p12 | Core와 Memory의 역할 |
| Figure 2, p15 | Clock 경로 |
| Figure 10, p38; Table 17, p39 | Memory map과 Peripheral 주소 |

## 공개 Source 바로 열기

아래 링크는 같은 Commit의 실제 Source와 설정입니다. 별도의 설치 없이 브라우저에서 확인할 수 있습니다. 정답을 먼저 보기보다 각 자료에서 근거를 찾아 제출양식에 기록하세요.

1. [readme.txt](https://github.com/STMicroelectronics/STM32CubeF0/blob/e220bfb12a162cfbf3bb65663e987e0d6550e9b4/Projects/STM32F030R8-Nucleo/Examples/GPIO/GPIO_IOToggle/readme.txt)
   - 경로: `Projects/STM32F030R8-Nucleo/Examples/GPIO/GPIO_IOToggle/readme.txt`
2. [.cproject](https://github.com/STMicroelectronics/STM32CubeF0/blob/e220bfb12a162cfbf3bb65663e987e0d6550e9b4/Projects/STM32F030R8-Nucleo/Examples/GPIO/GPIO_IOToggle/SW4STM32/STM32F030R8-Nucleo/.cproject)
   - 경로: `Projects/STM32F030R8-Nucleo/Examples/GPIO/GPIO_IOToggle/SW4STM32/STM32F030R8-Nucleo/.cproject`
3. [.project](https://github.com/STMicroelectronics/STM32CubeF0/blob/e220bfb12a162cfbf3bb65663e987e0d6550e9b4/Projects/STM32F030R8-Nucleo/Examples/GPIO/GPIO_IOToggle/SW4STM32/STM32F030R8-Nucleo/.project)
   - 경로: `Projects/STM32F030R8-Nucleo/Examples/GPIO/GPIO_IOToggle/SW4STM32/STM32F030R8-Nucleo/.project`
4. [STM32F030R8Tx_FLASH.ld](https://github.com/STMicroelectronics/STM32CubeF0/blob/e220bfb12a162cfbf3bb65663e987e0d6550e9b4/Projects/STM32F030R8-Nucleo/Examples/GPIO/GPIO_IOToggle/SW4STM32/STM32F030R8-Nucleo/STM32F030R8Tx_FLASH.ld)
   - 경로: `Projects/STM32F030R8-Nucleo/Examples/GPIO/GPIO_IOToggle/SW4STM32/STM32F030R8-Nucleo/STM32F030R8Tx_FLASH.ld`
5. [startup_stm32f030x8.s](https://github.com/STMicroelectronics/STM32CubeF0/blob/e220bfb12a162cfbf3bb65663e987e0d6550e9b4/Projects/STM32F030R8-Nucleo/Examples/GPIO/GPIO_IOToggle/SW4STM32/startup_stm32f030x8.s)
   - 경로: `Projects/STM32F030R8-Nucleo/Examples/GPIO/GPIO_IOToggle/SW4STM32/startup_stm32f030x8.s`
6. [main.c](https://github.com/STMicroelectronics/STM32CubeF0/blob/e220bfb12a162cfbf3bb65663e987e0d6550e9b4/Projects/STM32F030R8-Nucleo/Examples/GPIO/GPIO_IOToggle/Src/main.c)
   - 경로: `Projects/STM32F030R8-Nucleo/Examples/GPIO/GPIO_IOToggle/Src/main.c`
7. [system_stm32f0xx.c](https://github.com/STMicroelectronics/STM32CubeF0/blob/e220bfb12a162cfbf3bb65663e987e0d6550e9b4/Projects/STM32F030R8-Nucleo/Examples/GPIO/GPIO_IOToggle/Src/system_stm32f0xx.c)
   - 경로: `Projects/STM32F030R8-Nucleo/Examples/GPIO/GPIO_IOToggle/Src/system_stm32f0xx.c`
8. [stm32f0xx_it.c](https://github.com/STMicroelectronics/STM32CubeF0/blob/e220bfb12a162cfbf3bb65663e987e0d6550e9b4/Projects/STM32F030R8-Nucleo/Examples/GPIO/GPIO_IOToggle/Src/stm32f0xx_it.c)
   - 경로: `Projects/STM32F030R8-Nucleo/Examples/GPIO/GPIO_IOToggle/Src/stm32f0xx_it.c`
9. [stm32f0xx_nucleo.h](https://github.com/STMicroelectronics/stm32f0xx-nucleo-bsp/blob/9c947f2311227fab2c158350d541ad7ad29cce3d/stm32f0xx_nucleo.h)
   - 경로: `stm32f0xx_nucleo.h`
10. [stm32f0xx_hal.c](https://github.com/STMicroelectronics/stm32f0xx_hal_driver/blob/115eb1dc87e26ea29f4f2ca58003650381aabba2/Src/stm32f0xx_hal.c)
   - 경로: `Src/stm32f0xx_hal.c`

## 추가 추적 자료

- [HAL RCC 구현](https://github.com/STMicroelectronics/stm32f0xx_hal_driver/blob/115eb1dc87e26ea29f4f2ca58003650381aabba2/Src/stm32f0xx_hal_rcc.c)
- [HAL GPIO 구현](https://github.com/STMicroelectronics/stm32f0xx_hal_driver/blob/115eb1dc87e26ea29f4f2ca58003650381aabba2/Src/stm32f0xx_hal_gpio.c)
- [고정 Source의 Submodule 선언](https://github.com/STMicroelectronics/STM32CubeF0/blob/e220bfb12a162cfbf3bb65663e987e0d6550e9b4/.gitmodules)

## ARM Build를 추가로 선택한 경우

이번 과제의 필수 실행은 제공된 Host project의 `make test`와 `make stages`입니다. 별도로 실제 ARM Build를 추가하려면 전체 경로 구조와 Driver 의존성을 유지하세요. GitHub ZIP은 Submodule 내용을 자동으로 포함하지 않습니다.

별도의 실습 경로에서 다음과 같이 기준 Source를 받을 수 있습니다. 큰 Package이므로 시간이 걸릴 수 있습니다. 이미 받은 Project가 있다면 먼저 현재 변경 사항을 확인하고 별도의 경로를 사용하세요.

```sh
git clone --branch v1.11.5 --depth 1 https://github.com/STMicroelectronics/STM32CubeF0.git
cd STM32CubeF0
git rev-parse HEAD
git submodule update --init --recursive
git submodule status
```

`git rev-parse HEAD`가 위 고정 Commit과 같은지 확인합니다. Build를 수행하려면 해당 SW4STM32 Project를 지원하는 환경에서 같은 Directory 구조로 열고, 실제 IDE와 Compiler version을 기록합니다. 다른 IDE로 옮겼다면 변경한 설정과 절차도 남기세요. 분석 과제를 위해 특정 IDE를 설치하거나 구매할 필요는 없습니다.

## 이번 제품 요구사항과 연결하기

공개 예제의 File은 MCU 구조와 HAL 사용을 추적하는 근거입니다. 이번 제품의 LED Pull·Speed·반복 간격 등은 [요구사항](README.md)의 값으로 구현합니다. 공개 예제의 수치를 그대로 복사하지 말고 차이를 설명하세요.

공개 STM32 Project의 Startup 분석과 이번 Host test 실행은 확인 범위가 다릅니다. Host 실행에는 MCU의 Vector table과 Reset Handler가 사용되지 않으므로, Host test 통과를 실제 Board 실행 결과로 표시하지 않습니다.

제공 starter 전체를 자기 `submissions/week04/YOUR_GITHUB_ID/`로 복사하고 코드를 구현합니다. 제출 방법과 필수 Log는 [PR 제출 안내](SUBMISSION.md)를 따릅니다.
