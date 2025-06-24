# Project Description
이 프로젝트는 자체 게임 엔진을 개발하며 3D 그래픽스 렌더링과 게임 엔진 아키텍처의 근본 원리를 학습하기 위한 목적으로 시작되었습니다.
Win32 API 기반의 기초적인 윈도우 창 생성과 메시지 루프 처리부터 시작하여, DirectX 11 기반의 렌더링 파이프라인을 직접 구현을 목표로 하고 있습니다. 
모듈화를 통해 게임 엔진의 핵심 기능과 클라이언트(게임 실행 및 로직)를 명확히 분리하여, 시스템의 유지보수성과 확장성을 향상시켰습니다.

## Development Environment
- ' Window OS '
- ' Visual Studio 2022 '

## ⚠️ Caution

`Application::Initialize()` 함수에서 `Fmod::Initialize()`가 호출되는 순간부터 빌드가 안 되는 경우가 생깁니다.

**클라이언트 프로젝트 설정**에서 반드시 아래 스크립트를 추가하세요.

### 프로젝트 설정 필수 항목

1. **C/C++ → 일반 → 추가 포함 디렉터리**
```
$(SolutionDir)..\JaehuruEngine\External\FMOD\lib\x64
```
3. **링커 → 일반 → 추가 라이브러리 디렉터리**
```
$(SolutionDir)..\JaehuruEngine\External\FMOD\lib\x64
```
4. **링커 → 입력 → 추가 종속성**
```
fmod_vc.lib
fmodstudio_vc.lib
fmodL_vc.lib
fmodstudioL_vc.lib
```
5. **빌드 이벤트 → 빌드 후 이벤트**
```
IF "$(Configuration)"=="Debug" (
    xcopy /Y /D "$(SolutionDir)..\JaehuruEngine\External\FMOD\lib\x64\fmodL.dll" "$(OutDir)"
    xcopy /Y /D "$(SolutionDir)..\JaehuruEngine\External\FMOD\lib\x64\fmodstudioL.dll" "$(OutDir)"
) ELSE (
    xcopy /Y /D "$(SolutionDir)..\JaehuruEngine\External\FMOD\lib\x64\fmod.dll" "$(OutDir)"
    xcopy /Y /D "$(SolutionDir)..\JaehuruEngine\External\FMOD\lib\x64\fmodstudio.dll" "$(OutDir)"
)
```
---
# Version 1
***Win32 API*** 기반 아키텍처 및 기본 렌더링 구조 

## V1.00

### 윈도우 및 메시지 처리  
- WinMain 진입점 및 메시지 루프 처리 흐름 이해  
- PeekMessage 기반 논블로킹 메시지 루프 구현  

### 그래픽스 기초  
- Device Context(DC) 및 스톡 오브젝트 사용법 학습  
- GDI+를 통한 이미지 렌더링 및 배경 출력  
- 도형 렌더링 및 이동 구현을 통한 프레임 기반 구조 이해  
- 더블 버퍼링 원리 및 flickering 방지 기법 적용  

### 애플리케이션 구조  
- 정적/동적 라이브러리의 차이와 활용  
- Application 클래스 설계 및 루프 관리 구조 도입  

### 게임 오브젝트 및 아키텍처  
- GameObject 기반 오브젝트 추상화 구조 설계  
- Component 기반 아키텍처 도입 (Entity-Component 구조)  
- 2D Vector 클래스 직접 구현 및 연산 처리  
- Transform을 통한 Position, Rotation, Scale 통합 관리 구조 도입  
- Camera Component 구현 및 뷰 변환 처리 도입  
- Layer 구조 설계로 오브젝트 렌더링 순서 제어  
- Scene 및 SceneManager 클래스 구현을 통한 씬 전환 구조 구축  
- Scene 전환 시 상태 제어용 Enter(), Exit() 함수 구현  
- 오브젝트 동적 생성을 위한 Instantiate 함수 구현  
- 게임 오브젝트 활성 상태 제어(SetActive) 및 제거(Destroy) 함수 구현  
- DontDestroyOnLoad 클래스 구현
- TileMapRenderer, ToolScene 클래스 구현  
- 타일맵 윈도우 생성과 배치  
- 타일맵 저장 및 불러오기 기능  
- 카메라 타겟팅 설정  

### 애니메이션 및 렌더링  
- Animator 및 Animation 클래스 구현, AlphaBlend 테스트  
- BMP 이미지 32비트 알파 채널 여부에 따른 알파 블렌딩 / BitBlt 처리 자동 분기  
- 픽셀 투명화 처리 및 알파 블렌딩 구현  
- 포인터 함수를 이용한 애니메이션 이벤트 시스템 구현  
- 애니메이션 리소스 폴더 기반 자동 클립 생성(CreateAnimationByFolder 함수)  

### 게임 로직 및 AI  
- DeltaTime을 통한 성능 독립적 시간 처리  
- 상태 기반 FSM 패턴 적용 및 간단한 AI 행동 로직 구성  
- FSM 패턴 활용  

### 물리 및 충돌 처리  
- Collider 컴포넌트 구현  
- Collision Manager : 충돌체 레이어 마스킹 체크 및 로직  
- OnCollision 함수 구현  
- 충돌체 종류별 구현: AABB(rect-rect), circle-circle, rect-circle  
- Rigidbody : 가속도, 이동, 힘, 중력 작용 구현  
- 픽셀 기반 충돌 판정 시스템

### UI 시스템  
- UIManager, UIBase, UIButton, UIHUD 구현  

### 리소스 및 메모리 관리  
- Resource 관리 시스템 구현 (텍스처 등)  
- Memory Leak 체크용 _CrtSetDbgFlag() 함수 활용

### 오디오 관련 기능
- FMOD Studio API를 통해 사운드 로드 및 재생 기능 구현
- AudioListener, AudioSource, AudioClip 클래스 구현

### 서브모듈 기반 엔진 구조 개편
- 엔진을 Git 서브모듈 형태로 독립적인 버전 관리
- 정적 라이브러리 프로젝트에 핵심 엔진 코드 정리

## V1.01

### CreateAnimationByFolder 함수 버그 사항 수정
- `Animator::CreateAnimationByFolder`애니메이션이 하나만 출력되는 버그 사항을 수정
  
### Lerp(Linear Interpolation) 함수 추가
- Vector2 구조체에 Lerp 함수를 추가

## V1.02

### GameObject의 부모-자식 계층 구조 설계
- `AddChild` ,  `FindChildOfType` , `RemoveChild` 계층 구조 관련 함수들을 구현
- 주요 트래킹 (댕글링 포인터와 컨테이너 순회 중 삭제 문제) 이슈 해결

### Animator Update
- `GetActiveAnimationName` 함수 추가
- `Stop` 함수 추가

### UIManager 리팩토링
- UI Factory 패턴 적용
---
# Version 2
***DirectX 11*** 기반 그래픽스 파이프라인 및 엔진 아키텍처 확장

## V2.00

---
# Bug Issue 

### `Animator::CreateAnimationByFolder` 사용 시 애니메이션이 하나만 출력되는 버그
- **버그 상황**  
  `CreateAnimationByFolder`를 사용해 폴더 내 여러 이미지들을 기반으로 애니메이션을 생성할 때, 파일명을 `"0"`, `"1"`, `"2"` 등 단순한 형식으로 지정하면 **가장 먼저 생성한 애니메이션만 반복적으로 출력되는 현상**이 발생함.
- **원인 분석**  
  `Resources::Load` 함수 내부에서 리소스를 `std::map`에 **fileName을 key로 저장**하기 때문에, 동일한 파일명을 가진 리소스들이 이후에 덮어지지 않고 **이미 존재하는 리소스를 그대로 반환**하면서 생긴 문제였음.
- **해결 방법**  
  `fileName`만으로는 고유한 key가 되지 않으므로, 다음과 같이 **애니메이션 이름(`name`)과 파일 이름을 조합한 key**를 사용하여 중복을 방지함.

### `GameObject`의 부모-자식 계층 구조 설계 중, 삭제 시점과 접근 시점이 어긋나면서 예외 발생
- **버그 상황**
  `GameObject`의 부모-자식 계층 구조 설계 중, 삭제 시점과 접근 시점들이 어긋나면서 댕글링 포인터 (Dangling Pointer), 컨테이너 수정 중 순회 (Iterator Invalidation) 예외 발생
- **원인 분석**
  GameObject에서 사용하는 Destroy()는 즉시 삭제가 아닌 지연 삭제 구조로 생길 수 있는 예외 들이 너무 많음
- **해결 방법**
  관련 함수들 꼼꼼히 예외 처리하고 호출 시점을 점검 해주는 것으로 해결

---

# Reflections
엔진 아키텍처를 리팩토링하는 과정에서 큰 흥미를 느낄 수 있었다. 구조가 점차 명확해지고 체계적으로 정리되면서, 엔진과 클라이언트 간의 역할이 분리되고 각각의 책임이 분명해지는 점이 특히 인상적이었다. 이러한 경험을 통해 엔진 개발에 대한 흥미가 더욱 깊어졌고, 나아가 언리얼 엔진의 구조를 분석하고 직접 구현해보고자 하는 동기 또한 생겼다. 
