import os
import re
import sys

def fix_usb_buffer_sizes(root_dir):
    """
    Находит и заменяет размеры буферов USB HID в файлах usbd_customhid.h
    """
    # Шаблоны для поиска и замены
    patterns = [
        (r'^\s*#define\s+CUSTOM_HID_EPIN_SIZE\s+.*', '#define CUSTOM_HID_EPIN_SIZE                 64U'),
        (r'^\s*#define\s+CUSTOM_HID_EPOUT_SIZE\s+.*', '#define CUSTOM_HID_EPOUT_SIZE                64U'),
        (r'^\s*#define\s+USBD_CUSTOMHID_OUTREPORT_BUF_SIZE\s+.*', '#define USBD_CUSTOMHID_OUTREPORT_BUF_SIZE  64U'),
    ]

    count_files = 0
    count_replacements = 0

    # Рекурсивный обход директорий
    for root, dirs, files in os.walk(root_dir):
        for file in files:
            if file == 'usbd_customhid.h':
                file_path = os.path.join(root, file)
                print(f"\nОбрабатывается файл: {file_path}")

                # Чтение содержимого файла
                with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()

                file_modified = False

                # Отладочный вывод: поиск всех шаблонов
                for pattern, replacement in patterns:
                    matches = re.findall(pattern, content, flags=re.MULTILINE)
                    if matches:
                        print(f"🔍 Найдено по шаблону '{pattern}':")
                        for m in matches:
                            print(f"    → {m}")
                    else:
                        print(f"⚠️  Не найдено по шаблону: {pattern}")

                    # Замена
                    new_content, num_replacements = re.subn(pattern, replacement, content, flags=re.MULTILINE)
                    if num_replacements > 0:
                        content = new_content
                        count_replacements += num_replacements
                        file_modified = True
                        print(f"  ✅ Заменено: {num_replacements} вхождений на '{replacement}'")

                # Если были произведены замены, записываем файл обратно
                if file_modified:
                    with open(file_path, 'w', encoding='utf-8') as f:
                        f.write(content)
                    count_files += 1
                    print(f"💾 Файл обновлен: {file}")

    print(f"\nИтог: изменено {count_replacements} определений в {count_files} файлах.")

    return count_replacements


if __name__ == "__main__":
    if len(sys.argv) > 1:
        root_directory = sys.argv[1]
    else:
        root_directory = os.getcwd()

    print(f"Поиск и замена размеров буферов USB HID в директории: {root_directory}")
    replacements = fix_usb_buffer_sizes(root_directory)

    if replacements > 0:
        print("\n✅ Успешно! Размеры буферов USB HID изменены на 64 байта.")
    else:
        print("\n⚠️  Предупреждение: определения не найдены или уже установлены в нужные значения.")

    input("\nНажмите Enter для завершения...")
