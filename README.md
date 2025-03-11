# Systemy_Operacyjne2
Projekt 1: Problem ucztujących filozofów, wykonany w C++ z użyciem biblioteki std::thread, Autor: Cyprian Kozubek 272959

Instrukcje uruchomienia projektu:
Całość kodu projektowego znajduje się w branchu "master", program należy sklonować do używanego IDE, sprawdzić poprawność posiadanych bibliotek, 
wykonać konfigurację run/debug -> CMakeApplication, target: SystemyOperacyjne2, executable: SystemyOperacyjne2.

Opis problemu:
Problem ucztujących filozofów - Jest to problem, w którym przy stole ucztuje n-filozofów, a na stole znajduje się n-widelców. Filozof w danym momencie może wykonywać dwie czynności: myśleć lub jeść. Aby jeść dany filozof potrzebuję dwóch widelców, jednego po prawej i jednego po lewej, wtedy przez określony czas je, wykorzystując widelce, a następnie odkłada je ponownie na stół. Widelce w użyciu nie mogą być użyte przez żadnego innego filozofa, jeśli filozof, w danym momencie nie może uzyskać dostęp do dwóch widelców, zaczyna myśleć przez określony czas.

Wątki i co reprezentują: Wątki w projekcie reprezentują n-filozofów, którzy mogą w danym momencie myśleć lub, jeśli mają dostęp do odpowiedniej liczby widelców, jeść.

Sekcje krytyczne i ich rozwiązanie: W programie występują trzy sekcje krytyczne:
1. Widelce, nie znajduje się ich na stole odpowiednia ilość aby każdy filozof naraz mógł jeść, przez co zmuszeni są do konkurencji o ten zasób. Widelce zabezpieczone są mutexami, gdy filozof nie otrzyma dwóch widelców niemożliwe jest aby zaczął jeść.
2. Zapis do konsoli, utworzono globalny mutex do synchronizacji zapisu do konsoli, bez tej sekcji wiele wątków naraz próbowało pisać do konsoli, co powodowało poprzeplatany, nieczytelny tekst.
3. Semafor ograniczający ilość jedzących filozofów naraz, w danym momencie może jeść tylko n-1 filozofów. Element wykorzystany, w celu uniknięcia zakleszczania (deadlock).
