# 3주차 탐사 장치 레지스터 제어

**26년 10월 1주차 Mission**

주제는 비트 연산, 레지스터 제어, `volatile`입니다. C 언어로 학습용 8비트 레지스터 값을 계산합니다. 실제 보드 없이 문제를 풀고 자신의 코드를 검증할 수 있습니다.

## 문제 상황

스누피의 탐사 장치가 멈췄습니다. 기존 설정을 보존하면서 전원을 켜고 끄고, 탐사 모드를 설정하고, 준비 신호를 읽도록 아래 함수의 초안을 검토하세요.

## 레지스터와 동작 조건

비트 번호는 **오른쪽부터 0**입니다. 이 환경에서는 `uint8_t`를 사용할 수 있습니다.

| 레지스터 | 위치 | 의미 |
| --- | --- | --- |
| CTRL | bit0 | ENABLE: 0은 꺼짐, 1은 켜짐 |
| CTRL | bits2:1 | MODE: 00 대기, 01 저속, 10 탐사, 11 사용 금지 |
| CTRL | bits7:3 | 다른 설정. 변경하지 않고 유지 |
| STATUS | bit3 | READY |

- CTRL은 **일반 읽기/쓰기 8비트 값**이고 STATUS는 읽기 전용입니다.
- 읽기 부작용과 동시 변경은 없다고 가정합니다.
- 아래 네 함수는 실제 하드웨어 주소에 접근하지 않고 전달받은 값을 계산해 반환합니다.
- **새로 지정할 `mode` 인자는 0~2**입니다.
- **기존 CTRL의 MODE가 11이어도 수정 가능한 입력**입니다. 기존 값과 새 인자의 허용 범위를 구분하세요.
- CTRL 값을 바꾸는 세 함수는 대상 비트만 바꾸고 나머지를 모두 보존해야 합니다. MODE 변경 시 ENABLE도 보존하며, ENABLE 변경 시 MODE도 보존합니다.
- `is_ready`는 STATUS에서 READY를 추출해 숫자 **0 또는 1**을 반환합니다.

## 검토할 원본 코드

[starter/register_control.c](starter/register_control.c)에 과제 문서의 개선 전 네 함수를 그대로 보존했습니다.

```c
#include <stdint.h>
uint8_t enable(uint8_t ctrl) { return 0x01u; }
uint8_t set_mode(uint8_t ctrl, uint8_t mode) {
    return ctrl | (mode << 1);
}
uint8_t disable(uint8_t ctrl) { return 0; }
uint8_t is_ready(uint8_t status) {
    return status == 0x08u;
}
```

초안에는 의도적인 논리 오류가 있습니다. 함수만 있는 검토용 소스이며 `main`이나 정답 구현은 포함하지 않습니다. 각 함수가 어떤 요구 조건을 놓치는지 분석하고 자신의 제출 폴더에서 수정하세요.

## 구현 과제

1. `enable`은 기존 ENABLE이 0이든 1이든 **항상 1**로 만듭니다.
2. `disable`은 ENABLE을 **항상 0**으로 만듭니다.
3. `set_mode`는 bits2:1을 지정한 값으로 **교체**합니다.
4. `is_ready`는 READY만 읽어 숫자 **0 또는 1**을 반환합니다.

마스크와 시프트로 각 함수를 수정하고 **모든 근본 원인**을 설명하세요. 어떤 비트를 바꾸며 어떤 비트를 보존하는지, MODE를 바꿀 때 OR만 사용해도 되는지, STATUS 전체 값을 비교하면 어떤 경우를 놓치는지 검토합니다.

수정한 코드만 제시하지 말고 원인별로 **실패 상황 → 요구 조건과의 차이 → 수정 이유 → 검증 결과**를 연결해 설명하세요. 문제에서 보장한 조건 밖의 검토 사항을 원래 코드의 필수 오류와 혼동하지 않습니다.

## 실행 전 예상하고 실행 후 비교하기

아래 호출은 **각각 독립된 입력**입니다. 이전 호출의 결과를 다음 호출의 초기값으로 사용하지 않습니다.

```c
enable(0xA8)
enable(0xA9)
set_mode(0xAB, 2)
set_mode(0xAF, 2)
disable(0xAD)
is_ready(0x09)
is_ready(0x01)
```

[cases.csv](cases.csv)는 이 일곱 입력을 기록한 작성 양식입니다. 원문에서 직접 예측하도록 요구하므로 `expected_return`과 `actual_return`을 비워 두었습니다. 자신의 제출 폴더에 복사해 **실행 전에 예상값**, **실행한 뒤 실제값**을 채우고 비교하세요. 수정해야 하는 비트와 보존해야 하는 비트도 함께 확인합니다.

| 확인할 내용 | 제출할 근거 |
| --- | --- |
| ENABLE 설정과 해제 | 이미 켜진 경우와 꺼진 경우에도 요구한 상태가 되는지 |
| MODE 교체 | 기존 필드 값이 달라도 지정한 새 값으로 교체되는지 |
| 비대상 비트 보존 | 연산 전후 어떤 비트가 유지됐는지 |
| READY 추출 | 다른 상태 비트와 관계없이 0 또는 1을 반환하는지 |

필수 일곱 입력 외에 자신의 설명을 확인할 추가 입력을 테스트에 포함해도 됩니다. 예상값과 실제 실행값을 구분하고 빌드·실행 환경을 기록하세요.

## 하드웨어 상태를 읽는 선언

실제 MCU의 읽기 전용 STATUS를 읽으려 합니다. 플랫폼이 **유효한 주소와 접근 폭을 제공한다**고 가정하고, 다음 선언에 필요한 한정자를 붙이세요.

```c
uint8_t *status;
```

README에 다음 내용을 자신의 말로 설명합니다.

- 하드웨어가 값을 바꿀 수 있다는 점을 어떻게 표현했는가?
- 이 포인터를 통한 쓰기 제한을 어떻게 표현했는가?
- 각 한정자가 포인터 자체와 가리키는 값 중 어디에 적용되는가?
- `volatile`이 원자성이나 동기화까지 보장하는가?

이 항목은 **선언의 의미를 묻는 문항**입니다. 실제 하드웨어 주소를 실행하거나 예시 포인터를 역참조하는 테스트를 만들지 않습니다. 앞의 네 함수는 순수한 값 계산으로 검증합니다.

## PR 제출물

`submissions/week03/<자신의 GitHub 아이디>/`에 다음을 추가합니다.

1. 수정한 `register_control.c`와 필요한 헤더
2. 실행 가능한 `tests.c`와 필요한 테스트 파일
3. 일곱 입력의 예상값·실행값을 채운 `cases.csv` 또는 같은 내용을 담은 표
4. 모든 근본 원인, 연산의 선택 이유, 보존한 비트, 한정자 선언과 설명을 담은 `README.md`
5. 빌드·실행 명령, 실제 실행 결과, 아직 확인하지 않은 사항

학생 발표나 코드 리뷰에서 **어떻게 답변할지 보여 주는 완결된 문장**도 README에 작성하세요. 값이 우연히 맞았다는 설명으로 끝내지 않습니다.

## 제출 폴더 시작하기

먼저 [PR 제출 안내](../../CONTRIBUTING.md)의 Fork·clone·upstream 설정을 한 번 진행합니다. 아래 명령은 자신의 Fork를 복제한 저장소 루트에서 실행하며 `YOUR_GITHUB_ID`를 자신의 아이디로 바꿉니다. 저장하지 않은 작업이 있다면 먼저 정리하세요.

```sh
git fetch upstream
git switch -c solve/week03-YOUR_GITHUB_ID upstream/main
mkdir -p submissions/week03/YOUR_GITHUB_ID
cp weeks/week03/starter/register_control.c submissions/week03/YOUR_GITHUB_ID/register_control.c
cp weeks/week03/cases.csv submissions/week03/YOUR_GITHUB_ID/cases.csv
cp templates/submission/README.md submissions/week03/YOUR_GITHUB_ID/README.md
```

새 `tests.c`에 테스트용 `main`을 작성합니다. 구현과 테스트를 별도 소스로 뒀다면 다음처럼 빌드할 수 있습니다. 코드를 나누는 방식에 따라 명령을 조정하고 실제 사용한 명령을 README에 남기세요.

```sh
mkdir -p build/week03-YOUR_GITHUB_ID
cc -std=c11 -Wall -Wextra -Wpedantic \
  submissions/week03/YOUR_GITHUB_ID/register_control.c \
  submissions/week03/YOUR_GITHUB_ID/tests.c \
  -o build/week03-YOUR_GITHUB_ID/tests
./build/week03-YOUR_GITHUB_ID/tests
```

위 명령은 GCC/Clang 계열의 호스트 실행 예입니다. 원문은 C 버전을 지정하지 않았으며, 이 저장소에서는 C11 기준의 설명을 권장합니다. `.c` 파일을 직접 include한 뒤 같은 파일을 다시 링크하는 중복 빌드는 피하세요.

작성과 검증을 마치면 자기 폴더만 커밋·푸시하고 이 저장소의 `main`을 대상으로 PR을 보냅니다.

```sh
git add submissions/week03/YOUR_GITHUB_ID
git diff --cached
git commit -m "Solve week03 register control"
git push -u origin solve/week03-YOUR_GITHUB_ID
```

PR 제목 예시는 **`[week03] YOUR_GITHUB_ID 탐사 장치 레지스터 제어 개선`**입니다. 이미 해당 주차를 시작했다면 새로 복사해 덮어쓰지 말고 기존 브랜치와 제출 폴더를 이어서 수정하세요. `weeks/week03` 원본은 변경하지 않습니다.

## 학습 목표

- 마스크와 시프트로 비트 읽기와 설정·해제를 구현한다.
- 다른 필드의 값을 보존하며 지정한 필드를 교체한다.
- `volatile`을 포함한 한정자의 용도와 한계를 설명한다.

## 변경 기록

- 2026-09-27: 사용자 제공 「3주차 수업자료형 과제」의 조건, 원본 네 함수, 독립 입력 일곱 개와 선언 문항을 옮기고 PR 제출 절차를 추가했습니다.
