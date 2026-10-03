## 4주차 MCU 초기화 기능 구현

- GitHub 아이디:
- 제출 폴더: `submissions/week04/YOUR_GITHUB_ID/`
- 대상: `zinee-u/embedded-just-for-fun` / `main`

## 구현한 요구사항

| 요구사항 | 구현 File·함수 | 확인한 테스트와 결과 |
| --- | --- | --- |
| Memory 영역의 정상값·시작/끝 경계·영역 밖 주소 | | |
| HSI/PLL·SYSCLK·Bus 분주·실패 전달 | | |
| LED Port·Pin·Mode·Pull·Speed·초기 OFF·순서 | | |
| Application 초기화·실패 중단·재초기화·250 ms 반복 | | |

## 발견한 모든 근본 원인과 변경 이유

| 실패 입력 또는 상황 | 근본 원인 | 변경한 구현과 근거 | 실제 검증 결과 |
| --- | --- | --- | --- |
| | | | |

한 증상만 나열하지 말고 모든 요구조건을 확인합니다. 상세 설명은 자기 제출 `README.md`에 작성하고 해당 File을 안내해도 됩니다.

## 내가 추가한 테스트

- 추가한 경계·실패 상황 최소 2개:
- 제공 테스트와 별도로 확인하려는 위험:
- 예상 결과 / 실제 결과:

## Datasheet·Build·Startup 추적

- `TRACE.md` 위치:
- MCU 관계와 Clock 계산의 근거:
- 공개 STM32 Project에서 확인한 Build·Startup 흐름:
- `make stages`에서 직접 확인한 입력·출력:
- Source 분석 / Host 실행 / ARM Build / Board 실행의 구분:

## 재현 환경과 실행 결과

- OS:
- Compiler 이름·version:
- Make version:
- 실제 실행 위치와 명령:
- `make test` Exit code와 결과:
- `make stages` Exit code와 결과:
- `logs/test.log`, `logs/stages.log` 위치:
- 미확인 사항:

## Commit 이력

| 실제 Commit SHA | 목적 | 변경한 내용 |
| --- | --- | --- |
| | 구현 | |
| | 검증·환경 기록 | |

## Review에서 이렇게 설명하겠습니다

> 이 요구사항의 근거는 …입니다. 초안은 … 상황에서 … 조건을 지키지 못합니다. 저는 … File의 …을 변경했고, … 테스트를 실행해 …을 확인했습니다. Host에서는 …까지 확인했으며, 실제 Board의 …은 아직 확인하지 않았습니다.

## 제출 확인

- [ ] 네 `.c`에 요구값과 동작을 구현했습니다.
- [ ] 요구사항별 근본 원인과 수정 이유를 빠짐없이 설명했습니다.
- [ ] 고정 API와 제공 검증을 유지하고 자신의 추가 테스트를 작성했습니다.
- [ ] 최종 코드의 `make test`, `make stages`가 성공했고 실제 Log를 포함했습니다.
- [ ] `README.md`, `BUILD_ENV.md`, `TRACE.md`를 작성했습니다.
- [ ] 목적이 다른 본인 Commit을 최소 2개 남겼습니다.
- [ ] 원본 `weeks`와 다른 학생의 답안을 바꾸지 않았습니다.
- [ ] `build/`, 비밀 정보, 출제자 해설을 포함하지 않았습니다.
