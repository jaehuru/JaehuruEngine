## 프로젝트 소개
이 프로젝트는 자체 게임 엔진을 개발하며 3D 그래픽스 렌더링과 게임 엔진 아키텍처의 근본 원리를 학습하기 위한 목적으로 시작되었습니다.
Win32 API 기반의 기초적인 윈도우 창 생성과 메시지 루프 처리부터 시작하여, DirectX 11 기반의 렌더링 파이프라인을 직접 구현하고, 이후 실제 게임 제작까지 확장해 나갈 예정입니다.

## step1. Win32 API 기반 아키텍처 및 기본 렌더링 구조 학습

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

### UI 시스템  
- UIManager, UIBase, UIButton, UIHUD 구현  

### 리소스 및 메모리 관리  
- Resource 관리 시스템 구현 (텍스처 등)  
- Memory Leak 체크용 _CrtSetDbgFlag() 함수 활용  

