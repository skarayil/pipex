# 🚰 Pipex - Unix Pipe Mekanizmasını Simüle Eden Program

<div align="center">

![42 School](https://img.shields.io/badge/School-42-black?style=for-the-badge&logo=42)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Pipex](https://img.shields.io/badge/Project-pipex-blue?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)

**Unix shell'deki pipe mekanizmasını C dilinde simüle eden program**

*Bu proje, süreçler arası iletişim (IPC), dosya tanımlayıcıları ve Unix sistemlerinde temel pipe kullanımını derinlemesine öğretir.*

[Kurulum](#-kurulum) • [Kullanım](#-kullanım) • [Özellikler](#-desteklenen-özellikler) • [Bonus](#-bonus-kısmı)

</div>

---

## 🎯 Projenin Amacı

<img align="right" alt="Pipe Mechanism Animation" width="300" src="https://media0.giphy.com/media/v1.Y2lkPTc5MGI3NjExdnNoamd0ZXlhd2MxNjMwNGdheTUzZnVzbDZtOHBsZDhzZDhqZGR1cSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/xAKhG9iFXynDh2LEg5/giphy.gif">

Bu proje, **Unix shell'deki pipe (|) operatörünün** davranışını C dilinde yeniden oluşturmayı amaçlar. Shell'de kullandığımız `cmd1 | cmd2` yapısının arka planında çalışan mekanizmaları öğreterek, sistem programlama konusunda derinlemesine deneyim kazandırır.

### 🎓 **Ana Öğrenme Hedefleri:**

#### 🔗 **Pipe Mekanizması**
- Unix pipe'larının çalışma prensibi
- `pipe()` sistem çağrısı ve file descriptor yönetimi
- İki süreç arasında veri aktarımı
- STDIN/STDOUT yönlendirme teknikleri

#### 🖥️ **Process Management**
- `fork()` ile çocuk süreç oluşturma
- Parent-child process ilişkileri ve coordination
- Process lifecycle ve state management
- `wait()` ve `waitpid()` ile süreç senkronizasyonu

#### 📁 **File Descriptor Manipulation**
- `dup2()` ile file descriptor kopyalama
- STDIN (0), STDOUT (1), STDERR (2) yönlendirme
- File descriptor inheritance between processes
- Resource cleanup ve file descriptor management

#### ⚙️ **Command Execution**
- `execve()` sistem çağrısı ile program çalıştırma
- PATH environment variable parsing
- Command line argument handling
- Command validation ve error handling

#### 🔍 **Environment Variables**
- `envp` array manipulation
- PATH variable parsing ve directory search
- Environment inheritance in child processes
- Dynamic path resolution

#### 🛡️ **Error Handling ve Resource Management**
- System call error handling
- Resource leak prevention (file descriptors, memory)
- Graceful error recovery
- Comprehensive error reporting

---

## ✨ Desteklenen Özellikler

<div align="center">

![Pipe Communication](https://img.shields.io/badge/Pipe-Communication-brightgreen?style=for-the-badge)
![Process Control](https://img.shields.io/badge/Process-Control-blue?style=for-the-badge)
![File Redirection](https://img.shields.io/badge/File-Redirection-orange?style=for-the-badge)

</div>

### 📋 **Ana Fonksiyonalite**

| Component | Sorumluluk | Sistem Çağrısı |
|-----------|------------|----------------|
| **Input File** | Dosyadan veri okuma | `open()`, `dup2()` |
| **First Command** | İlk komutu çalıştırma | `fork()`, `execve()` |
| **Pipe** | Süreçler arası veri aktarımı | `pipe()` |
| **Second Command** | İkinci komutu çalıştırma | `fork()`, `execve()` |
| **Output File** | Sonucu dosyaya yazma | `open()`, `dup2()` |

### 🔧 **Shell Eşdeğerliği**

```bash
# Shell command:
< infile cmd1 | cmd2 > outfile

# Pipex equivalent:
./pipex infile cmd1 cmd2 outfile
```

#### 📊 **Veri Akış Diyagramı**

```
infile → [STDIN] → cmd1 → [PIPE] → cmd2 → [STDOUT] → outfile
          ↑                  ↓                 ↑
       Child 1          File Desc          Child 2
                        [0] [1]
```

#### 🔄 **Execution Flow**

1. **File Opening**: Input file açılır ve STDIN'e yönlendirilir
2. **First Fork**: İlk child process oluşturulur
3. **Pipe Creation**: Pipe oluşturulur (read end [0], write end [1])
4. **First Command**: cmd1 çalıştırılır, output pipe'a yazılır
5. **Second Fork**: İkinci child process oluşturulur
6. **Second Command**: cmd2 çalıştırılır, pipe'dan okur
7. **Output File**: Sonuç output file'a yazılır
8. **Cleanup**: Tüm file descriptor'lar kapatılır, processes beklenir

---

## 🎁 Bonus Kısmı

<div align="center">

![Multiple Pipes](https://img.shields.io/badge/Multiple-Pipes-gold?style=for-the-badge)
![Here Doc](https://img.shields.io/badge/Here-Doc-purple?style=for-the-badge)

</div>

Bonus kısmı, programın yeteneklerini genişleterek daha karmaşık senaryoları destekler:

### 🔀 **Multiple Pipes**

| Özellik | Açıklama | Shell Eşdeğeri |
|---------|----------|----------------|
| **N Commands** | Sınırsız sayıda komut | `cmd1 \| cmd2 \| cmd3 \| ...` |
| **Chain Pipes** | Birbirine bağlı pipe'lar | Multiple `\|` operators |
| **Sequential Execution** | Sıralı komut çalıştırma | Pipeline execution |

```bash
# Shell:
< file1 cmd1 | cmd2 | cmd3 | cmd4 > file2

# Pipex bonus:
./pipex file1 cmd1 cmd2 cmd3 cmd4 file2
```

### 📝 **Here_doc Support**

#### 🎯 **Here_doc Özelliği**
```bash
# Shell:
cmd1 << LIMITER | cmd2 >> file

# Pipex bonus:
./pipex here_doc LIMITER cmd1 cmd2 file
```

| Aspect | Davranış | Implementation |
|--------|----------|----------------|
| **Input Mode** | STDIN'den okuma | `get_next_line()` |
| **Limiter** | Sonlandırma kelimesi | String comparison |
| **Output Mode** | Append mode | `O_APPEND` flag |
| **Interactive** | Kullanıcı girişi | Real-time input |

#### 🔄 **Here_doc Çalışma Prensibi**

```
User Input → here_doc> prompt → Compare with LIMITER
    ↓                                    ↓
Write to                            Match? → Stop
Temp Pipe                           No Match → Continue
    ↓
Pass to cmd1 → PIPE → cmd2 → APPEND to outfile
```

---

## 📁 Dosya Yapısı

```
pipex/
│
├── 📄 Makefile                         # Build automation
│
├── 🗂️ mandatory/
│   ├── pipex.c                         # Ana program logic
│   ├── pipex.h                         # Header ve struct tanımları
│   └── utils.c                         # Yardımcı fonksiyonlar
│
├── 🎁 bonus/
│   ├── pipex_bonus.c                   # Multiple pipes + here_doc
│   ├── pipex_bonus.h                   # Bonus header
│   ├── utils_bonus.c                   # Bonus utilities
│   └── inits_bonus.c                   # Here_doc implementation
│
├── 📚 library/
│   ├── libft/                          # Custom C library
│   │   ├── ft_split.c
│   │   ├── ft_strjoin.c
│   │   └── ...
│   └── get_next_line/                  # Line reading utility
│       ├── get_next_line.c
│       └── get_next_line_utils.c
│
└── 📖 README.md                        # Proje dokümantasyonu
```

### 📊 **Dosya Açıklamaları**

| Dosya | İçerik | Sorumluluk |
|-------|--------|------------|
| `pipex.c` | Ana program | Process management, pipe creation |
| `utils.c` | Helper functions | Path finding, command execution |
| `pipex_bonus.c` | Enhanced version | Multiple pipes, here_doc |
| `inits_bonus.c` | Initialization | Here_doc handling, file setup |
| `libft/` | Custom library | String manipulation, memory utilities |
| `get_next_line/` | Line reader | Here_doc input reading |

---

## 🚀 Kurulum

### 📋 **Ön Gereksinimler**

![GCC](https://img.shields.io/badge/GCC-Required-red?style=flat-square&logo=gnu&logoColor=white)
![Make](https://img.shields.io/badge/Make-Required-blue?style=flat-square&logo=gnu&logoColor=white)
![Unix](https://img.shields.io/badge/Unix-Compatible-green?style=flat-square&logo=linux&logoColor=white)

- **C Compiler**: `clang` veya `gcc`
- **Unix-like System**: Linux, macOS, WSL
- **Process Management**: Fork ve exec desteği

### 📥 **Repository Klonlama**

```bash
# Projeyi yerel sisteminize klonlayın
git clone https://github.com/skarayil/pipex.git
cd pipex
```

### 🔨 **Derleme İşlemi**

```bash
# Temel versiyonu derle
make

# Bonus versiyonu derle
make bonus

# Temizlik işlemleri
make clean          # Object dosyalarını sil
make fclean         # Tüm oluşturulan dosyaları sil
make re             # Yeniden derle (fclean + make)
```

### 📦 **Çıktı Dosyaları**

```bash
pipex              # Temel executable (2 komut)
pipex_bonus        # Bonus executable (N komut + here_doc)
```

---

## 💻 Kullanım

### 🖥️ **Temel Kullanım (Mandatory)**

#### 🟢 **Basit Pipe Örneği**

```bash
# Dosyadan oku, grep ile filtrele, wc ile say, sonucu dosyaya yaz
./pipex infile "grep hello" "wc -l" outfile

# Shell eşdeğeri:
< infile grep hello | wc -l > outfile
```

#### 🟡 **Komut Örnekleri**

```bash
# Listing komutları
./pipex infile "ls -l" "grep txt" outfile

# Text processing
./pipex infile "cat" "tr 'a-z' 'A-Z'" outfile

# Word count ve sorting
./pipex infile "cat" "wc -w" outfile
```

### 🎁 **Bonus Kullanım**

#### 🟣 **Multiple Pipes**

```bash
# 3 komutlu pipeline
./pipex_bonus infile "cat" "grep pattern" "wc -l" outfile

# Shell eşdeğeri:
< infile cat | grep pattern | wc -l > outfile

# 5 komutlu complex pipeline
./pipex_bonus file1 "cat" "grep a" "sort" "uniq" "wc -l" file2

# Shell eşdeğeri:
< file1 cat | grep a | sort | uniq | wc -l > file2
```

#### 🔴 **Here_doc Kullanımı**

```bash
# Interactive input mode
./pipex_bonus here_doc EOF "grep hello" "wc -l" outfile

# Örnek kullanım:
heredoc> hello world
heredoc> this is a test
heredoc> hello again
heredoc> EOF
# 'hello' içeren satır sayısı outfile'a append edilir
```

### 📝 **Kod Örnekleri**

#### 🟢 **Ana Pipeline Logic**

```c
#include "pipex.h"

void ft_pipex(t_pipex *p, char **envp)
{
    p->envp = envp;
    p->files.infile = -1;
    p->files.outfile = -1;
    ft_paths(p);  // PATH'den yolları parse et
    
    if (pipe(p->files.tube) == -1)
        ft_eerror(ERR_PIPE, p);
}

int main(int ac, char *av[], char **envp)
{
    t_pipex p;
    int status;
    
    if (ac != 5)
        return (write(2, ERR_INPUT, ft_strlen(ERR_INPUT)), 1);
    
    ft_pipex(&p, envp);
    
    // First child: infile → cmd1 → pipe
    p.child_1 = fork();
    if (p.child_1 == 0)
        ft_infile(&p, av);
    
    // Second child: pipe → cmd2 → outfile
    p.child_2 = fork();
    if (p.child_2 == 0)
        ft_outfile(&p, av);
    
    // Parent: close pipes and wait
    close(p.files.tube[0]);
    close(p.files.tube[1]);
    waitpid(p.child_1, NULL, 0);
    waitpid(p.child_2, &status, 0);
    
    ft_free(p.paths);
    return (WIFEXITED(status) ? WEXITSTATUS(status) : 0);
}
```

#### 🟡 **Command Execution**

```c
void ft_execute(char *argv, t_pipex *p)
{
    char **cmd;
    char *path;
    int i;
    
    cmd = ft_split(argv, ' ');  // "ls -l" → ["ls", "-l"]
    if (!cmd || !cmd[0])
        ft_eerror(ERR_EMPTY, p);
    
    // Absolute path kontrolü
    if (ft_strchr(cmd[0], '/') && execve(cmd[0], cmd, p->envp) == -1)
        ft_eerror(ERR_EXECVE, p);
    
    // PATH'de ara
    i = -1;
    while (p->paths && p->paths[++i])
    {
        path = ft_build_path(p->paths[i], cmd[0]);
        execve(path, cmd, p->envp);  // Başarılı olursa return etmez
        free(path);
    }
    
    // Komut bulunamadı
    ft_free(cmd);
    write(2, ERR_CMD, ft_strlen(ERR_CMD));
    exit(127);
}
```

#### 🔴 **Bonus: Here_doc Implementation**

```c
void ft_heredoc(t_pipex *p)
{
    int fd[2];
    char *line;
    
    if (pipe(fd) == -1)
        ft_eexit(ERR_PIPE, p);
    
    while (1)
    {
        write(1, "heredoc> ", 9);
        line = get_next_line(0);  // STDIN'den oku
        
        if (!line)
            break;
        
        // Limiter kontrolü
        if (ft_strncmp(line, p->io.limiter, ft_strlen(p->io.limiter)) == 0
            && line[ft_strlen(p->io.limiter)] == '\n')
        {
            free(line);
            break;
        }
        
        write(fd[1], line, ft_strlen(line));  // Pipe'a yaz
        free(line);
    }
    
    close(fd[1]);
    if (dup2(fd[0], STDIN_FILENO) == -1)
        ft_eexit(ERR_DUP, p);
    close(fd[0]);
}
```

#### 🟣 **Bonus: Multiple Pipes**

```c
void ft_process(char *cmd, t_pipex *p)
{
    int fd[2];
    pid_t pid;
    
    if (pipe(fd) == -1)
        ft_eexit(ERR_PIPE, p);
    
    pid = fork();
    if (pid == 0)  // Child
    {
        close(fd[0]);  // Read end'i kapat
        if (dup2(fd[1], STDOUT_FILENO) == -1)
            ft_eexit(ERR_DUP, p);
        close(fd[1]);
        ft_execute(cmd, p);
    }
    else  // Parent
    {
        close(fd[1]);  // Write end'i kapat
        if (dup2(fd[0], STDIN_FILENO) == -1)
            ft_eexit(ERR_DUP, p);
        close(fd[0]);
    }
}

int main(int ac, char *av[], char **envp)
{
    t_pipex p;
    int i, mode, count;
    
    // ... initialization ...
    
    ft_check(&p, &i, &mode);  // here_doc kontrolü
    
    count = ac - 1 - i;
    while (i < ac - 2)
        ft_process(av[i++], &p);  // Her komut için pipe
    
    ft_last(av[ac - 2], &p, mode);  // Son komut
    
    while (count-- >= 0)
        wait(NULL);  // Tüm child'ları bekle
    
    return (0);
}
```

---

## 🧪 Test Senaryoları

### ✅ **Temel Fonksiyonalite Testleri**

#### 📊 **Basit Pipeline Testleri**

```bash
# Setup test dosyası
echo -e "Hello World\nTest Line\nAnother Line" > infile

# Test 1: Cat ve grep
./pipex infile "cat" "grep Hello" outfile
cat outfile  # Beklenen: Hello World

# Test 2: Ls ve grep
./pipex infile "ls -l" "grep pipex" outfile

# Test 3: Word count
./pipex infile "cat" "wc -w" outfile
cat outfile  # Beklenen: 6 (word count)
```

#### 🔤 **Komut Çeşitleri**

```bash
# Text transformation
./pipex infile "cat" "tr 'a-z' 'A-Z'" outfile
cat outfile  # Beklenen: Uppercase text

# Sorting
./pipex infile "cat" "sort" outfile

# Unique lines
./pipex infile "sort" "uniq" outfile

# Head/tail commands
./pipex infile "cat" "head -n 3" outfile
./pipex infile "cat" "tail -n 2" outfile
```

### 🎁 **Bonus Testleri**

#### 🔄 **Multiple Pipes**

```bash
# 3 komutlu test
./pipex_bonus infile "cat" "grep a" "wc -l" outfile

# Shell karşılaştırması
< infile cat | grep a | wc -l > expected
diff outfile expected  # Sonuçlar aynı olmalı

# 5 komutlu complex pipeline
./pipex_bonus infile "cat" "grep test" "sort" "uniq" "wc -l" outfile

# Shell eşdeğeri ile karşılaştır
< infile cat | grep test | sort | uniq | wc -l > expected
diff outfile expected
```

#### 📝 **Here_doc Testleri**

```bash
# Interactive here_doc testi
./pipex_bonus here_doc EOF "cat" "wc -l" outfile
heredoc> Line 1
heredoc> Line 2
heredoc> Line 3
heredoc> EOF

cat outfile  # Beklenen: 3

# Here_doc ile grep
./pipex_bonus here_doc STOP "grep hello" "wc -l" outfile
heredoc> hello world
heredoc> test line
heredoc> hello again
heredoc> STOP

cat outfile  # Beklenen: 2

# Append mode kontrolü
./pipex_bonus here_doc END "cat" "tr 'a-z' 'A-Z'" outfile
# outfile'a append edilmeli (üzerine yazmamalı)
```

### ⚠️ **Hata Durumu Testleri**

#### 🚫 **Invalid Input Tests**

```bash
# Eksik argument
./pipex
./pipex infile cmd1
./pipex infile cmd1 cmd2

# Geçersiz dosya
./pipex nonexistent "cat" "wc -l" outfile
# stderr'a error message yazmalı, exit code 1

# Geçersiz komut
./pipex infile "invalidcmd" "cat" outfile
# "Command not found" error, exit code 127

# Permission hatası
chmod 000 infile
./pipex infile "cat" "wc -l" outfile
# Permission denied error
chmod 644 infile
```

#### 🛡️ **Edge Cases**

```bash
# Boş dosya
touch empty_file
./pipex empty_file "cat" "wc -l" outfile
cat outfile  # Beklenen: 0

# Çok büyük dosya
dd if=/dev/zero of=large_file bs=1M count=100
./pipex large_file "cat" "wc -c" outfile

# Özel karakterli komutlar
./pipex infile "echo 'test'" "cat" outfile
./pipex infile "grep -E '[0-9]+'" "sort" outfile
```

### 📈 **Performance Testleri**

#### ⚡ **Throughput Measurement**

```bash
# Büyük dosya işleme
time ./pipex large_file "cat" "wc -l" outfile

# Multiple pipes performance
time ./pipex_bonus large_file "cat" "grep a" "sort" "uniq" "wc -l" outfile

# Shell ile karşılaştırma
time < large_file cat | grep a | sort | uniq | wc -l > shell_output
```

#### 🔍 **Memory Leak Kontrolü**

```bash
# Valgrind ile test
valgrind --leak-check=full --show-leak-kinds=all ./pipex infile "cat" "wc -l" outfile

# Bonus versiyon memory testi
valgrind --leak-check=full ./pipex_bonus infile "cat" "grep a" "sort" outfile

# Here_doc memory testi
valgrind --leak-check=full ./pipex_bonus here_doc EOF "cat" "wc -l" outfile <<< $'Line1\nLine2\nEOF'
```

---

## 🛠️ Teknik Detaylar

### 🏗️ **System Architecture**

```
Program Flow:
│
├── Main Process
│   ├── Parse Arguments
│   ├── Open Files (infile/outfile)
│   ├── Parse PATH environment
│   └── Create Pipe
│
├── Child Process 1
│   ├── dup2(infile, STDIN)
│   ├── dup2(pipe[1], STDOUT)
│   ├── Close unused FDs
│   └── execve(cmd1)
│
└── Child Process 2
    ├── dup2(pipe[0], STDIN)
    ├── dup2(outfile, STDOUT)
    ├── Close unused FDs
    └── execve(cmd2)
```

### 🔧 **File Descriptor Management**

#### 📊 **FD Flow Diyagramı**

```
Parent Process:
STDIN  (0) → Terminal
STDOUT (1) → Terminal
STDERR (2) → Terminal
pipe[0] (3) → Pipe read end
pipe[1] (4) → Pipe write end
infile  (5) → Input file
outfile (6) → Output file

Child 1:
STDIN  (0) ← dup2(infile)
STDOUT (1) ← dup2(pipe[1])
STDERR (2) → Terminal
pipe[0], pipe[1], infile, outfile → Closed

Child 2:
STDIN  (0) ← dup2(pipe[0])
STDOUT (1) ← dup2(outfile)
STDERR (2) → Terminal
pipe[0], pipe[1], infile, outfile → Closed
```

#### 🎯 **dup2() Usage Pattern**

```c
// Child 1: infile → STDIN, pipe write → STDOUT
dup2(infile_fd, STDIN_FILENO);   // 0 ← infile
dup2(pipe[1], STDOUT_FILENO);    // 1 ← pipe write end

// Child 2: pipe read → STDIN, outfile → STDOUT
dup2(pipe[0], STDIN_FILENO);     // 0 ← pipe read end
dup2(outfile_fd, STDOUT_FILENO); // 1 ← outfile
```

### ⏱️ **Process Synchronization**

#### 🔄 **Wait Strategy**

```c
// Parent process'te:
waitpid(child_1, NULL, 0);        // İlk child'ı bekle
waitpid(child_2, &status, 0);     // İkinci child'ı bekle

// Exit status kontrolü
if (WIFEXITED(status))
    return (WEXITSTATUS(status));  // Child'ın exit code'unu döndür
```

| Wait Function | Purpose | Use Case |
|---------------|---------|----------|
| `wait(NULL)` | Herhangi bir child'ı bekle | Simple cases |
| `waitpid(pid, &status, 0)` | Specific child'ı bekle | Exit status needed |
| `waitpid(-1, NULL, WNOHANG)` | Non-blocking wait | Polling |

### 📈 **PATH Resolution Algorithm**

```c
Algorithm: find_command_path()
│
├── 1. Check if command has '/'
│   └── Yes? Use as absolute path → execve()
│
├── 2. Parse PATH environment variable
│   ├── Split by ':'
│   └── Get directory list
│
├── 3. For each directory:
│   ├── Construct full path
│   ├── Check access(X_OK)
│   └── Found? → execve()
│
└── 4. Command not found
    └── Exit with 127
```

### 🎨 **Data Structures**

```c
// Main structure
typedef struct s_pipex
{
    t_files files;      // File descriptors
    char    **envp;     // Environment variables
    char    **paths;    // Parsed PATH directories
    pid_t   child_1;    // First child PID
    pid_t   child_2;    // Second child PID
} t_pipex;

// File management
typedef struct s_files
{
    int infile;         // Input file FD
    int outfile;        // Output file FD
    int tube[2];        // Pipe FDs [read, write]
} t_files;

// Bonus: IO handling
typedef struct s_io
{
    int     infile;
    int     outfile;
    int     heredoc;    // Here_doc mode flag
    char    *limiter;   // Here_doc limiter string
} t_io;
```

---

## 📚 Notlar

### ⚠️ **Önemli Dikkat Edilmesi Gerekenler**

#### 🛡️ **File Descriptor Management**
- **Close Unused FDs**: Her child process'te kullanılmayan FD'leri kapat
- **Leak Prevention**: Parent process'te tüm FD'leri kapat
- **Error Handling**: FD operations başarısız olursa cleanup yap
- **Order Matters**: dup2() öncesi doğru FD'lerin açık olduğundan emin ol

#### 🔧 **Process Management**
- **Fork Error Check**: fork() return value her zaman kontrol edilmeli
- **Wait for Children**: Zombie process'leri önlemek için wait() kullan
- **Exit Codes**: Child process'ler doğru exit code ile çıkmalı (127 for command not found)
- **Signal Handling**: SIGPIPE ve diğer signal'lara dikkat et

#### 💾 **Memory Management**
- **PATH Parsing**: ft_split() ile ayrılmış memory'yi free et
- **Command Arguments**: ft_split() ile oluşturulan array'i free et
- **Valgrind Clean**: Hiçbir memory leak olmamalı
- **Error Paths**: Error durumlarında da cleanup yapılmalı

#### ⚡ **Performance Considerations**
- **Minimal fork()**: Sadece gerekli child process'leri oluştur
- **Efficient PATH Search**: İlk match'te dur
- **Buffer Sizes**: Optimal buffer size kullan (bonus: get_next_line)
- **Resource Limits**: System limits'e dikkat et (max open files, etc.)

### 💡 **Best Practices**

#### 🎯 **Robust Design:**
1. **Error Handling**: Her sistem çağrısının return value'sunu kontrol et
2. **Resource Cleanup**: Error durumlarında da cleanup yap
3. **Modular Functions**: Her fonksiyon tek bir sorumluluk
4. **Clear Structure**: t_pipex struct ile state management
5. **Defensive Programming**: NULL checks, boundary conditions

#### 🔍 **Debugging Tips:**
```bash
# System call tracing
strace ./pipex infile "cat" "wc -l" outfile

# FD tracking
lsof -p $(pgrep pipex)

# Process tree
pstree -p $(pgrep pipex)

# Memory debugging
valgrind --track-fds=yes ./pipex infile "cat" "wc -l" outfile
```

### 🧰 **Geliştirme Araçları**

#### 📊 **Testing Tools:**
```bash
# Automatic testing script
#!/bin/bash
TESTS=("cat|wc -l" "grep a|sort" "ls -l|head -n 5")

for test in "${TESTS[@]}"; do
    cmd1=$(echo $test | cut -d'|' -f1)
    cmd2=$(echo $test | cut -d'|' -f2)
    
    # Pipex output
    ./pipex infile "$cmd1" "$cmd2" pipex_out
    
    # Shell output
    < infile $cmd1 | $cmd2 > shell_out
    
    # Compare
    diff pipex_out shell_out && echo "✅ $test" || echo "❌ $test"
done
```

#### 🔬 **Debug Makefile Target:**
```makefile
debug: CFLAGS += -g -fsanitize=address
debug: re

leak: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) infile "cat" "wc" out
```

---

## 🏆 Proje Başarıları

<div align="center">

![Score](https://img.shields.io/badge/Score-125%2F100-gold?style=for-the-badge)
![Tests](https://img.shields.io/badge/Tests-All%20Passed-success?style=for-the-badge)
![Norminette](https://img.shields.io/badge/Norminette-OK-brightgreen?style=for-the-badge)
![Bonus](https://img.shields.io/badge/Bonus-Completed-orange?style=for-the-badge)

### 📊 **Proje İstatistikleri**

| Metrik | Değer |
|--------|-------|
| **Source Files** | 8 |
| **Functions** | 20+ |
| **System Calls** | `fork`, `pipe`, `dup2`, `execve`, `wait` |
| **Test Cases** | 30+ |
| **Supported Commands** | Unlimited |
| **Memory Leak Tests** | ✅ Valgrind Clean |
| **Multiple Pipes** | ✅ N commands support |
| **Here_doc** | ✅ Implemented |

</div>

---

<div align="center">

### 🎯 **Core Skills Gained**

![Process Management](https://img.shields.io/badge/Process-Management-blue?style=flat-square)
![Pipe Communication](https://img.shields.io/badge/Pipe-Communication-green?style=flat-square)
![File Descriptors](https://img.shields.io/badge/File-Descriptors-orange?style=flat-square)
![System Calls](https://img.shields.io/badge/System-Calls-red?style=flat-square)
![IPC](https://img.shields.io/badge/IPC-purple?style=flat-square)

---

**🚰 "Pipex teaches you that Unix pipes are not magic—they're just clever file descriptor manipulation."**

*Bu proje, Unix sistemlerinin temel building block'larını öğreterek, sistem programlama konusunda sağlam bir temel oluşturur.*

---

### 👨‍💻 Created by Sude Naz Karayıldırım

[![42 Profile](https://img.shields.io/badge/42%20Profile-skarayil-black?style=flat-square&logo=42&logoColor=white)](https://profile.intra.42.fr/users/skarayil)
[![GitHub](https://img.shields.io/badge/GitHub-skarayil-181717?style=flat-square&logo=github&logoColor=white)](https://github.com/skarayil)

**⭐ Eğer bu proje işinize yaradıysa, repo'ya star vermeyi unutmayın!**

</div>
