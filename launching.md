# Запуск программы

## Компиляция
```
$ cmake -H. -B_builds
$ cmake --build _builds 
$ cd _builds
```
## Выполнение

Для сжатия используются флаги `-с` или `--compress`:

```
$ ./main -c input.txt output.txt
```
```
$ ./main --compress input.txt output.txt
```

Для распаковки используются флаги `-d` или `-decompress`:

```
$ ./main -d input.txt output.txt
```
```
$ ./main --decompress input.txt output.txt
```

## Формат входных данных

## Формат выходных данных
