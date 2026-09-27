# Embedded Just for Fun

스누피와 함께 C 코드를 읽고, 문제의 원인을 찾아 고치는 주차별 과제 저장소입니다. 수정 전 코드와 문제를 공개하고, 개선한 코드·설명·실행 결과를 Pull Request로 제출합니다.

## 이번 과제

| 주차 | 주제 | 문제 | 수정 전 코드 |
| --- | --- | --- | --- |
| 2주차 | 자료형과 배열, 메모리와 포인터 | [와이퍼 센서값 변환](weeks/week02/README.md) | [decode_rain.c](weeks/week02/starter/decode_rain.c) |

`week02`는 수업 회차입니다. 달력의 월별 주차나 제출 마감일을 뜻하지 않습니다.

## 과제 풀기

1. 주차별 문제를 읽고 이 저장소를 **Fork**합니다.
2. 자신의 Fork에서 과제용 브랜치를 만듭니다.
3. 원본을 `submissions/week02/<자신의 GitHub 아이디>/`로 복사합니다.
4. 코드를 고치고 테스트와 원인 분석을 작성합니다.
5. 이 저장소의 `main`을 대상으로 PR을 보냅니다.

처음 GitHub로 제출한다면 [PR 제출 안내](CONTRIBUTING.md)를 순서대로 따라 하세요. PR 제목은 `[week02] <GitHub 아이디> 와이퍼 센서값 변환 개선`처럼 작성합니다.

## 폴더 구조

```text
weeks/
  week02/
    README.md                 # 문제와 요구 조건
    starter/decode_rain.c     # 개선 전 함수 원본
    cases.csv                # 요구 조건 확인용 입력과 예상 결과
submissions/
  week02/<github-id>/         # 학생별 PR로 추가
    decode_rain.c            # 자신의 개선 코드
    tests.c                  # 자신의 테스트
    README.md                # 근본 원인, 설계, 실행 결과
templates/
  week/README.md              # 새 주차 문제 작성 양식
  submission/README.md        # 학생 답변 작성 양식
docs/
  WEEKLY_MAINTENANCE.md       # 매주 과제 추가와 PR 운영
.github/
  pull_request_template.md    # PR 작성 시 표시되는 양식
```

## 운영 원칙

- `weeks`에는 항상 개선 전 코드와 문제를 보존합니다.
- 풀이 PR은 자기 `submissions` 폴더에 제출합니다. 원본이나 다른 사람의 답안을 덮어쓰지 않습니다.
- 증상 한 개만 고치는 것으로 끝내지 않고, 문제의 근본 원인을 모두 찾아 설명합니다.
- 정답 구현을 한 가지로 고정하지 않습니다. 요구 조건을 만족하는지, 선택한 방식의 근거와 단점을 설명하는지 함께 봅니다.
- 실행 결과에는 실제로 실행한 환경과 결과를 적습니다. 예상값을 실행값으로 표시하지 않습니다.
- 병합된 제출물과 공개 PR은 다른 사람도 볼 수 있습니다. 독립 풀이가 목적이라면 자신의 첫 답안을 만든 뒤 다른 PR을 참고하세요.

이 저장소는 학습용입니다. `starter`의 코드는 수정할 결함을 포함한 원본입니다. 전체 코드와 입력 조건을 검토하기 전에 그 결과를 제어 명령에 사용하지 마세요.

출제자는 [매주 관리 안내](docs/WEEKLY_MAINTENANCE.md)를 참고합니다.
