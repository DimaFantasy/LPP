import os
import re
import sys

def fix_usb_buffer_sizes(root_dir):
    """
    Находит и заменяет размеры буферов USB HID во всех файлах usbd_customhid.h
    """
    patterns = [
        (r'^\s*#define\s+CUSTOM_HID_EPIN_SIZE\s+.*', '#define CUSTOM_HID_EPIN_SIZE                 64U'),
        (r'^\s*#define\s+CUSTOM_HID_EPOUT_SIZE\s+.*', '#define CUSTOM_HID_EPOUT_SIZE                64U'),
        (r'^\s*#define\s+USBD_CUSTOMHID_OUTREPORT_BUF_SIZE\s+.*', '#define USBD_CUSTOMHID_OUTREPORT_BUF_SIZE  64U'),
    ]

    total_found = 0
    total_replaced = 0
    total_files_changed = 0
    modified_files = []

    # Рекурсивный обход директорий
    for root, dirs, files in os.walk(root_dir):
        for file in files:
            if file == 'usbd_customhid.h':
                file_path = os.path.join(root, file)
                print(f"\n📂 Обрабатывается файл: {file_path}")

                with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()

                file_modified = False
                file_found = 0
                file_replaced = 0

                for pattern, replacement in patterns:
                    matches = re.findall(pattern, content, flags=re.MULTILINE)
                    if matches:
                        file_found += len(matches)
                        print(f"   🔍 Найдено {len(matches)} по шаблону '{pattern}':")
                        for m in matches:
                            print(f"       → {m}")
                    else:
                        print(f"   ⚠️  Не найдено по шаблону: {pattern}")

                    new_content, num_replacements = re.subn(pattern, replacement, content, flags=re.MULTILINE)
                    if num_replacements > 0:
                        file_replaced += num_replacements
                        content = new_content
                        file_modified = True
                        print(f"   ✅ Заменено {num_replacements} → '{replacement}'")

                if file_modified:
                    with open(file_path, 'w', encoding='utf-8') as f:
                        f.write(content)
                    total_files_changed += 1
                    modified_files.append((file_path, file_found, file_replaced))
                    print(f"💾 Файл обновлен: найдено {file_found}, заменено {file_replaced}")
                else:
                    print("➡️  Изменений нет")

                total_found += file_found
                total_replaced += file_replaced

    print(f"\nИтог: найдено {total_found}, изменено {total_replaced} определений в {total_files_changed} файлах.")

    if modified_files:
        print("\n📋 Список изменённых файлов:")
        for f, found, replaced in modified_files:
            print(f"  • {f} — найдено {found}, заменено {replaced}")

    return total_replaced


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
