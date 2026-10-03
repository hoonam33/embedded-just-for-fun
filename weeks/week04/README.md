# 4주차 MCU 초기화 기능 구현 요청서

**주제: MCU 구조 · Build · 초기화 · Git 관리**

스누피는 STM32F030R8 기반 제품의 초기화 기능을 개발팀에 요청합니다. Datasheet와 ST 공개 예제를 확인하고, 아래 요구값이 실제 C 구현에 반영되도록 작성해 주세요. 수정한 코드와 실행 결과를 이 저장소의 `main`을 대상으로 하는 Pull Request로 제출합니다.

## 학습 목표

- MCU의 메모리·클록·주변장치 관계를 데이터시트에서 확인한다.
- 공개 예제의 빌드 과정과 시작 코드·초기화 순서를 추적한다.
- 프로젝트 모듈을 나누고 Git으로 변경 이력과 빌드 환경을 기록하는 방법을 익힌다.

## 개발 범위와 기준 자료

- MCU는 **STM32F030R8**, Board는 **NUCLEO-F030R8**입니다.
- Datasheet는 **DS9773 Rev 5**입니다. Family 최대 사양과 STM32F030R8의 사양을 구분하세요.
- 공개 예제는 **STM32CubeF0 v1.11.5**, Commit `e220bfb12a162cfbf3bb65663e987e0d6550e9b4`의 `GPIO_IOToggle`입니다.
- 공개 예제의 `SW4STM32` Project 설정, Linker script, Startup, `main.c`를 읽습니다. 정확한 경로와 링크는 [자료 안내](REFERENCES.md)에 있습니다.
- 구현은 이 과제의 [starter](starter/)에서 시작합니다. 실제 Hardware 주소를 PC에서 역참조하지 않습니다.

공개 예제는 구조와 API 사용의 근거입니다. 이번 제품의 요구값과 공개 예제의 설정이 모두 같다고 가정하지 마세요. 아래 요구사항을 우선 적용하고, 공개 예제와 달라지는 설정은 이유를 기록합니다.

## 개발 요청 1 — Memory map을 C 코드로 표현해 주세요

`src/memory_map.c`의 `memory_region(uint32_t address)`를 구현합니다. 단일 주소가 어느 영역에 속하는지 판정해 다음 값을 반환하세요. 시작 주소와 끝 주소를 모두 포함합니다.

| 영역 | 시작 주소 | 크기 | 반환값 |
| --- | --- | --- | --- |
| Flash | `0x08000000` | 64 KiB | `MEMORY_FLASH` |
| SRAM | `0x20000000` | 8 KiB | `MEMORY_SRAM` |
| GPIOA | `0x48000000` | 1 KiB | `MEMORY_GPIOA` |
| RCC | `0x40021000` | 1 KiB | `MEMORY_RCC` |
| 위 네 영역 밖 | — | — | `MEMORY_UNKNOWN` |

1 KiB는 1024 Byte입니다. 끝 주소는 시작 주소와 크기로 계산해 확인하세요. 주소 값만 비교하며 그 주소에서 값을 읽거나 쓰지 않습니다. Boot alias와 다른 Peripheral은 이번 분류 범위에 포함하지 않습니다.

`TRACE.md`에 각 크기·주소의 Datasheet 근거를 적고, CPU·Flash·SRAM·RCC·GPIOA의 관계도를 추가합니다. CPU의 접근 경로와 Clock 공급·Enable 관계는 화살표의 뜻을 구분해 주세요.

## 개발 요청 2 — 요구 Clock이 설정되도록 구현해 주세요

`src/clock.c`의 `board_clock_init(void)`를 구현합니다.

| 설정 항목 | 제품 요구사항 |
| --- | --- |
| 기본 source | HSI 8 MHz |
| PLL 입력 | HSI / 2 |
| PLL 배수 | ×12 |
| SYSCLK | PLL, 48 MHz |
| AHB / APB1 분주 | 각각 /1 |
| Flash latency | 48 MHz 동작에 맞는 값 |
| 반환값 | 모든 Clock 설정 성공 시 `true`, 실패 시 `false` |

HAL 설정 구조체를 초기화하고 요구값을 채워 호출합니다. Oscillator 설정이 실패하면 다음 Clock 설정을 진행하지 않으며, Clock 설정 자체의 실패도 호출자에게 전달합니다. `true`를 무조건 반환하거나 문서에 주파수만 적는 것으로 완료되지 않습니다.

`TRACE.md`에는 실제 선택한 Clock 경로의 계산과 공개 Source의 근거를 적어 주세요. MCU의 최대 주파수와 Reset 직후의 상태가 같은 의미인지도 설명합니다.

## 개발 요청 3 — LED 설정과 제어의 책임을 나눠 주세요

`src/led.c`의 `board_led_init(void)`와 `board_led_toggle(void)`를 구현합니다.

| 설정 항목 | 제품 요구사항 |
| --- | --- |
| LED | GPIOA, Pin 5 |
| Mode | Output Push-Pull |
| Pull | NOPULL |
| Speed | LOW |
| 초기 상태 | OFF |
| 초기화 순서 | GPIOA Clock Enable → OFF 출력값 설정 → GPIO 설정 |

`board_led_toggle`은 위 LED만 Toggle합니다. Pin과 초기화 설정은 LED Module이 관리하고, Application은 LED Module의 API를 호출합니다. LED2의 실제 Port·Pin은 BSP에서 확인하고 Datasheet의 Peripheral 주소와 연결해 설명해 주세요.

## 개발 요청 4 — Application 초기화와 반복 동작을 구현해 주세요

`src/app.c`의 `app_init(void)`와 `app_step(void)`를 구현합니다.

- `app_init`은 **HAL 초기화 → Clock 초기화 → LED 초기화** 순서로 진행합니다.
- HAL 또는 Clock 초기화가 실패하면 `false`를 반환하고 남은 초기화 단계를 중단합니다.
- 모든 초기화가 성공하면 `true`를 반환합니다.
- 초기화 성공 전에는 `app_step`이 LED를 Toggle하거나 Delay를 수행하지 않습니다.
- 초기화 성공 후 `app_step` 한 번은 **LED Toggle → `HAL_Delay(250)`**을 수행합니다.
- 다시 초기화를 시도해 실패한 경우에도, 이전 성공 상태를 근거로 반복 동작을 계속하면 안 됩니다.

한 번의 Toggle 간격은 명목상 250 ms이며 ON/OFF 한 주기는 약 500 ms입니다. 이 값은 실제 Board에서 측정한 주기를 뜻하지 않습니다.

## Code 변경 범위

필수 구현은 `src/memory_map.c`, `src/clock.c`, `src/led.c`, `src/app.c`입니다. 공개 함수명·인자·반환형은 `include/mission.h`의 계약을 유지합니다. 각 File 안에 필요한 내부 함수와 상태를 추가할 수 있습니다.

`include/`, `host/`, `tests/test_mission.c`, 기본 `Makefile`은 제공된 검증 기준입니다. 검사를 우회하거나 예상값을 바꾸지 않습니다. 자신의 추가 검증은 `tests/test_student.c`에 작성하세요. 실제 Module 분리 결과가 위 네 `.c`에 남아야 하며, 문서만 제출하면 완료로 인정하지 않습니다.

## Build와 초기화 흐름을 추적해 주세요

`TRACE.md`에 다음 내용을 작성합니다.

1. **공개 STM32 Project:** 실제 Source 목록, Include·Define, Compiler 계열, Linker script와 Library 설정, 산출물을 설정 File에서 확인합니다. 명시되지 않은 Compiler version은 추정해서 쓰지 않습니다.
2. **Reset 이후:** 선택한 Startup의 Vector table과 `Reset_Handler`에서 `.data`, `.bss`, `SystemInit`, C Library 초기화, `main`으로 이어지는 실제 순서를 추적합니다. `SystemInit`과 `SystemClock_Config`의 역할도 구분합니다.
3. **이번 Host Build:** `make stages`를 실행하고 `.i` → `.s` → `.o` → Host 실행 File의 생성 과정을 설명합니다. 각 단계의 입력·출력과 도구의 역할을 기록합니다.
4. **Module 구조:** Memory map·Clock·LED·Application의 책임과 호출 방향을 설명합니다. Header의 선언과 `.c`의 구현이 Build에 각각 어떻게 참여하는지 적습니다.

Host 실행 File의 시작 과정이 MCU의 Vector table·Reset Handler를 대신 검증하는 것은 아닙니다. 공개 STM32 Source를 읽어 확인한 사실과 Host에서 실행한 결과를 나눠 기록하세요.

## 필수 검증과 완료 기준

자기 제출 폴더에서 `make test`와 `make stages`를 실제로 실행합니다. [제출 안내](SUBMISSION.md)에 Log 저장 명령이 있습니다.

| 확인할 내용 | 제출할 증거 |
| --- | --- |
| Memory 영역의 정상값·경계·영역 밖 입력 | C 구현과 Host test 결과 |
| Clock 설정값·호출 순서·실패 전달 | C 구현과 HAL 대역 호출 기록을 검사한 결과 |
| LED Pin·설정·초기화 순서 | C 구현과 Host test 결과 |
| Application의 성공·실패·재초기화 상태 | C 구현과 Host test 결과 |
| Build 단계와 공개 Startup의 차이 | `TRACE.md`와 `logs/stages.log` |
| 변경 이유와 재현 환경 | Commit 2개 이상, `BUILD_ENV.md`, PR 본문 |

제공 검증에 더해 자신의 경계·실패 사례를 최소 2개 `tests/test_student.c`의 `run_student_tests`에 추가하세요. `assert`가 실제로 조건을 검사하도록 작성합니다. 예상값, 실제값, 실패 원인과 수정 이유를 구분합니다. 초안이 요구사항을 놓치는 모든 지점을 찾아 **실패 상황 → 근본 원인 → 코드 변경 → 검증 결과**로 설명해 주세요.

이 테스트의 HAL은 PC에서 호출과 설정을 기록하는 대역입니다. 실제 RCC·GPIO Register, 전기적 LED 상태, Clock 정확도, 시간 측정까지 검증하지 않습니다. **ARM Build·Flash 기록·Board 실행은 추가 실습**이며 필수 Host test를 대신하지 않습니다.

## PR 제출물

```text
submissions/week04/YOUR_GITHUB_ID/
  src/                 # 본인이 완성한 네 Module
  include/             # 제공된 API와 설정 계약
  host/                # 제공된 Host HAL 대역
  tests/               # 제공 검증 + 자신의 추가 검증
  Makefile
  README.md            # 모든 근본 원인·변경 이유·검증 요약
  BUILD_ENV.md         # Source 기준·Compiler·명령·실행 범위
  TRACE.md             # Datasheet·Build·Startup·Module 분석
  logs/test.log        # 실제 make test 결과
  logs/stages.log      # 실제 make stages 결과
```

`build/`의 생성 File과 전체 ST SDK는 제출하지 않습니다. 원본 `weeks/week04`와 다른 학생의 제출도 수정하지 않습니다.

**구현 Commit과 검증·환경 기록 Commit을 구분해 최소 2개 Commit을 남긴 뒤 실제 PR을 여세요.** PR 제목은 `[week04] YOUR_GITHUB_ID MCU 초기화 기능 구현`입니다. 제출 대상은 `zinee-u/embedded-just-for-fun`의 `main`이며, 자기 Fork 안에서만 PR을 만들면 제출이 완료되지 않습니다.

- 처음부터 따라 하기: [Fork부터 PR까지](SUBMISSION.md)
- PR 본문 작성양식: [PR_BODY.md](PR_BODY.md)
- 상세 자료 링크: [REFERENCES.md](REFERENCES.md)

## 변경 기록

- 2026-10-03: 세 학습 목표를 C 구현·Host test·Build 추적·Git PR 제출로 확인하는 과제를 작성했습니다. `week04`는 수업 회차이며 별도 마감일을 뜻하지 않습니다.
