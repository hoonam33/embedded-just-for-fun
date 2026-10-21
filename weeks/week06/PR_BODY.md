# [06회차] YOUR_GITHUB_ID TC387QP Interrupt 수집 개선

## 문제와 개선 결과

어떤 입력·실행 순서에서 무엇이 잘못됐는지, 변경 후 어떻게 동작하는지 설명합니다.

## 모든 근본 원인

| 요구 조건 | 실패 입력 / 실행 순서 | 원본 실제 결과 | 근본 원인 | 변경 원리 | Test / 실제 결과 |
| --- | --- | --- | --- | --- | --- |
| 직접 작성 | | | | | |

하나의 증상만 고치고 끝내지 않습니다. 같은 원인에서 나온 여러 실패는 묶되, 수량·용량·출력 계약·Snapshot·IRQ 복구·실행 Context·Report 의미를 빠짐없이 검토합니다.

## 공식 근거와 설계 판단

| 문서 / 고정 Source | 절·페이지·함수 | 확인한 사실 | 이번 설계에 적용한 판단 |
| --- | --- | --- | --- |
| 직접 작성 | | | |

- Datasheet가 보장하는 사실과 10ms·용량 4·병합이라는 제품 정책을 구분했습니다.
- Polling / Interrupt 흐름도와 선택 조건: `CONCURRENCY.md`의 해당 항목을 연결합니다.
- 읽기·초기화 사이 ISR Timeline과 이전 IRQ 상태 보존: 실제 값을 설명합니다.
- Main 지연과 Interrupt 차단의 차이, 17ms 가정·B의 분석: 계산과 한계를 설명합니다.

## 검증

| 실행 | Exit code / 결과 | Log |
| --- | --- | --- |
| 원본 `make test` | 실제 결과 | `logs/before-test.log` |
| 개선 후 `make test` | 실제 결과 | `logs/test.log` |
| 개선 후 `make demo` | 실제 결과 | `logs/demo.csv` |
| 직접 추가한 Test 1 | 입력·예상·실제 | Test 함수명 |
| 직접 추가한 Test 2 | 입력·예상·실제 | Test 함수명 |

실제 환경은 `BUILD_ENV.md`에 기록합니다. Host의 가상 Tick·결정적 Hook 검증을 Board 실측으로 표시하지 않습니다.

## 변경 범위 확인

- [ ] `submissions/week06/YOUR_GITHUB_ID/`만 수정했습니다.
- [ ] 원본 Starter·제공 API·Host·고정 Test·Hook 계약을 유지했습니다.
- [ ] 추가 Test가 최소 2개이며 서로 다른 경계를 검증합니다.
- [ ] 모든 근본 원인과 실패 결과·수정 근거를 설명했습니다.
- [ ] Build 산출물·SDK 전체·인증 정보가 포함되지 않았습니다.
- [ ] Base가 `zinee-u/embedded-just-for-fun:main`입니다.
