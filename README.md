# Constellation_searching

개요
-------------
모바일 기기 분실을 대비한 모바일 위치 추적 앱입니다.  
미리 설정한 명령어를 분실한 모바일 기기에 전송하여 해당 기기의 위치정보를 SMS로 받아볼 수 있습니다.  
명령어를 통해 분실 기기의 배터리 잔량을 확인하고 배터리 절약 모드로 전환할 수 있습니다.

+ JAVA
+ Android Studio
+ GPS제어 및 주소변환
+ SMS송수신
+ SMS내용 검사를 통해 명령어 판별 
+ 배터리 잔량 확인 및 배터리 절약모드

실행 결과
-------------
+ 명령어 설정 단계
<p>
  <img src="" vspace="10">
</p>

+ 명령어를 송신하면 그에 대한 정보를 수신
<p>
   <img src="" vspace="10">
</p>

클래스 설계
-------------
+ MainService.java
<pre><code>
private GpsInfo gps;		// GPS 클래스
private int percent;
private String password;	// 위치 정보를 얻기 위한 명령어
private String passbattery;		// 배터리 잔량을 얻기 위한 명령어
private boolean getBatteryAction = false;
String number;
String text;

public int onStartCommand(Intent intent, int flags, int startId) 
private BroadcastReceiver mBatInfoReceiver = new BroadcastReceiver()	// 배터리잔량
private void sendSMS(String sendNumber, String sendText)		// 문자보내기
</code></pre>

+ GpsInfo.java
<pre><code>
private final Context mContext;
private boolean isGPSEnabled = false;		// 현재 GPS 사용유무
private boolean isNetworkEnabled = false;	// 네트워크 사용유무 
private boolean isGetLocation = false;		// GPS 상태값
Location location; 
double lat; 		// 위도 
double lon; 		// 경도
String mAddressStr;	// 주소
private static final long MIN_DISTANCE_CHANGE_FOR_UPDATES = 10;	// 최소 GPS 정보 업데이트 거리 10미터 
private static final long MIN_TIME_BW_UPDATES = 1000 * 60 * 1;	// 최소 GPS 정보 업데이트 시간 밀리세컨이므로 1분
protected LocationManager locationManager;
  
public GpsInfo(Context context)		// GPS 정보 반환
public void stopUsingGPS()		// GPS 종료
public double getLatitude()		// 위도값 반환
public double getLongitude()		// 경도값 반환
public boolean isGetLocation()		// 위치정보를 받아왔는지 확인
public boolean isLocationEnabled()	// GPS나 WIFI를 이용한 위치정보를 받아올 수 있는 상태인지 확인
public void showSettingsAlert()		// GPS정보를 받아오지 못했을 때 alert창
</code></pre>

+ SaveBattery.java
<pre><code>
public void Bright_control()	// 화면, 윈도우매니저 밝기 조절
</code></pre>

+ Sms.java
<pre><code>
String receiveNumber = "";
String receiveText = "";
    
public void onReceive(Context context, Intent intent)	// 메세지 내용 반환
public String getNumber ()				// 전화번호 반환
</code></pre>
