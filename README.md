# Isletim-Sistemleri

	SAKARYA ÜNİVERSİTESİ BİLGİSAYAR MÜHENDİSLİĞİ İŞLETİM SİSTEMLERİ PROJESİ
(2021-2022)


Proje: Kabuk Programı(Linux üzerinde basit bir komut yorumlayıcısı)
Grup Elemanları: 
b191210450 - Emir Önder Demircan
b191210080 - Mustafa Burak Aydın
b191210053 - Zeynep Aslan
B181210027 - İbrahim Şahin
b181210030 - Vedat Arslan



TASARIMA GENEL BAKIŞ:

 Proje istenenlere göre tasarlandı. Alınan girdi boşluklara göre parçalama işlemine sokuldu. Ardından her komut dolaşılarak başındaki ve sonundaki boşluklar temizlendi. Elde edilen komutlar string dizisi içinde saklandı.

Bütün kullanıcıdan girdi alma, bunu parçalayıp icra edilebilecek hale getiren fonksiyonlar KomutParsing.h adlı soyada yazıldı. Ana kaynak dosyasında parsing işlemi yapıldıktan sonra komut icraya gönderiliyor. Komut için fork() ile yeni proses oluşturuluyor ve ebeveyn prosesin child prosesi beklemesi sağlandı.

Dokümanda belirtilen built-in komutlar icradan önce kontrol ediliyor. Eğer ‘exit’ var ise sonlanıyor, ‘cd’ komutu var ise cdhdir() ile güncelleniyor ve ‘showpid’ var ise ekrana o ana kadar oluşturulmuş 5 child prosesin proses id leri yazdırılıyor. Bu veriler her child proses oluştuğunda id si diziye atanıyor. 5 den fazla oluşursa dizinin başından eklemeye devam ediyor.

Eğer bu komutlar dışında ise komut icrasında gönderiliyor ve fork(),execvp() sistem çağrıları kullanılarak proses icra ediliyor.

ÖZEL DURUMLAR:

 Bazı mevcut belirsizlikler var. İlki karmaşık girdiler. Hatalı ve karmaşık girdilier. Örneğin kelimeler arası fazla boşluklar farklı karakterler vs.  Parsing yapısı bu girdilerde sorunsuz çalışacak şekilde tasarlandı. Karmaşık girdilerde bile girilen komutları ayırabiliyor. Her kelimeyi ayrıt edebilecek şekilde tasarlandı. Böylece aradaki anlamsız girdilerden arındırılıyor. Yanlış komut girildiyse zaten execvp() hatalı dönüyor ve hata mesajı yazdırılıp yeni komut isteniyor.


PROGRAMDAKİ HATALAR VE BELİRSİZLİKLER:
 Program bütün istenenleri yerine getiriyor. Takılma, donma, kapanma durumu yok. Çalışmadığı durum yada durduk yere kapanma komutu icra etmememe doğru komuta hata verme durumu olmadı.

KARŞILAŞILAN ZORLUKLAR:
Program da ilginç bir yerde fazlasıyla zaman harcadım. Dokümanda da belirtildiği gibi komutlarımda çöp oluşumu sorunu oluştu. Yani belli girdiden sonra doğru komutu hatalı görme ya da fazladan kelime oluşma durumu gibi. Bu durumda dokümanda belirtilen memset() ve bzero() çağrılarını kullandım ama başarılı olmadı. Çözümü parçalama metodumda değişiklikler yaptım ve sanırım bu durum tekrarlamadı.




KAYNAK DOSYALAR:

KomutParsing.h : Kullanıcıdan girdi alır parçalayıp icra edilebilir hale getirir.
Kabuk.c :Program başlatılır. Komut icrası burada gerçekleşir.
Makefile :Derleme ve çalıştırma dosyası.

DERLEME VE ÇALIŞTIRMA TALİMATLARI:
Dizin içerisinde makefile dosyası mevcut ve içinde derleme ve çalıştırma komutları var. Dizinin içerisindeyken make komutu çağrıldığında program derlenip çalışmaktadır.

YARARLANILAN KAYNAKLAR:
https://stackoverflow.com/
https://brennan.io/2015/01/16/write-a-shell-in-c/
https://www.geeksforgeeks.org/
https://www.delftstack.com/howto/c/get-current-directory-in-c/


