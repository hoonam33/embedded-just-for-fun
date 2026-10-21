# 06회차 동시성·지연 근거 기록

## 문서에서 확인할 근거

| 확인할 사실 | 공식 문서·Version·위치 | 문서의 조건 | 구현 판단 | 확인 Test |
| --- | --- | --- | --- | --- |
| TC387QP의 STM / Interrupt 경로 | | | | |
| STM Compare 요청 처리와 다음 Compare 갱신 | | | | |
| CPU0 IRQ 금지와 이전 상태 복원 | | | | |
| `volatile` 접근과 복합 Read/Clear의 차이 | | | | |

## 경쟁 순서 재현

`platform_interleave()`를 Snapshot 읽기 뒤, 공유 값 Clear 전에 정확히 1회 유지합니다. 해당 지점에 IRQ가 도착할 때 Main과 ISR의 실행 순서, `pending / dropped / last_tick`의 전후 값을 기록합니다.

| 순서 | 실행 주체 | IRQ 상태 | Mailbox 값 | 지역 Snapshot | 근거 |
| --- | --- | --- | --- | --- | --- |
| 1 | | | | | |
| 2 | | | | | |
| 3 | | | | | |
| 4 | | | | | |

## 지연 분석

- Polling / Interrupt의 두 흐름도와 각각을 선택할 조건:
- 분석 가정 Sensor 2ms + Publish 15ms를 ISR에서 실행할 때와 Main에서 IRQ enabled / disabled로 실행할 때의 차이:
- 원본의 별도 Delay 10ms까지 포함하면 위 I/O 17ms 외에 어떤 지연이 더해지는지:
- Snapshot Critical section 시간 B가 추가하는 최대 차단과, 전체 Interrupt latency를 B로 단정할 수 없는 이유:
- Timer 요청 / ISR 실행 / Main에서 Sensor 읽기 시작을 구분한 Timeline:
- 짧은 ISR만으로 10 ms Sampling을 보장할 수 없는 이유:
- 10·20·30 ms 요청 뒤 Main 35 ms 실행 시 Report의 의미:
- 6회 요청을 아직 Main이 가져가지 않았을 때 `pending / dropped / last_tick`:
- 가장 긴 IRQ 금지 구간과 이를 줄인 방법:
- 실제 측정했다면 GPIO/Trace로 관찰한 ISR 지연과 Sampling 지연:

2ms·15ms는 분석용 가정이고 B는 미측정 시간입니다. 제공 Host의 Delay도 Sleep하지 않고 호출을 기록합니다.

Host의 숫자 Tick은 순서 검증용입니다. 10, 20, 30은 Demo에서 10 ms 간격을 읽기 쉽게 나타낸 값이며 실제 100 MHz STM Tick 변환이나 실제 Latency 측정값이 아닙니다. Hook은 단일 C Thread로 실행하고, IRQ가 금지되면 1-bit Pending으로 보류합니다. 여러 Hardware Compare를 모두 Queue에 저장하는 보장은 없습니다.
