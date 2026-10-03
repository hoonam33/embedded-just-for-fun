# 4주차 Datasheet · Build · Startup 추적

## 1. Datasheet 근거와 MCU 관계

| 구현한 값 | Datasheet 페이지·표·그림 또는 BSP 근거 | C File·함수와 사용 의미 |
| --- | --- | --- |
| Flash 영역 | | |
| SRAM 영역 | | |
| GPIOA 영역 / LED2 Port·Pin | | |
| RCC 영역 | | |
| HSI·PLL·SYSCLK·Bus Clock | | |

CPU·Flash·SRAM·RCC·GPIOA 관계도를 아래에 작성합니다. 주소 접근과 Clock 공급·Enable 화살표의 의미를 구분하세요.

```text
(본인의 관계도)
```

Clock 계산식과 공개 예제에서 선택한 경로:

## 2. 공개 예제와 제품 요구의 차이

| 항목 | 공개 예제의 설정·근거 | 이번 제품의 요구·변경한 C 위치 |
| --- | --- | --- |
| Clock | | |
| LED 초기 상태·Mode·Pull·Speed | | |
| Toggle 간격 | | |
| 실패 처리 | | |

## 3. 공개 STM32 Project의 Build

| 확인할 내용 | 실제 File·설정·근거 |
| --- | --- |
| Target / Compiler 계열 / Version 명시 여부 | |
| Source 입력 / Include / Define | |
| Startup Object / Linker script / Library | |
| 실행 Image와 후처리 산출물 | |

Header를 포함하는 것과 `.c`를 Build 입력에 넣는 것의 차이:

## 4. 공개 예제의 Reset부터 main까지

| 실제 순서 | File·함수·label | 준비하는 상태와 다음 단계의 관계 |
| --- | --- | --- |
| | | |

`SystemInit`과 `SystemClock_Config`의 호출 위치·역할 차이:

## 5. 내가 실행한 Host Build

| 단계 | 실제 입력 File | 실제 출력 File | Log의 명령·옵션과 역할 |
| --- | --- | --- | --- |
| Preprocess | | | |
| Compile | | | |
| Assemble | | | |
| Link | | | |

Host에서 검증한 내용 / ARM Source로만 확인한 내용 / Board에서 아직 확인하지 않은 내용:

## 6. Module과 초기화

네 `.c`의 책임과 호출 방향, 공개 API와 내부 상태를 설명합니다.

- memory_map.c:
- clock.c:
- led.c:
- app.c:

초기화 성공·실패·재초기화 실패 시 호출 순서와 `app_step` 동작:
