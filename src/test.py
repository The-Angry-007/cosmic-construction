import os

PRAGMA_ONCE = '#pragma once'

def get_include_path(root_dir, file_dir):
    # Compute relative depth from root
    rel_path = os.path.relpath(file_dir, root_dir)

    if rel_path == '.':
        return '#include "PCH.hpp"\n'
    
    depth = rel_path.count(os.sep) + 1
    return '#include "' + '../' * depth + 'PCH.hpp"\n'

def process_file(filepath, root_dir):
    with open(filepath, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    # Skip if already includes PCH.hpp (any form)
    if any('PCH.hpp' in line for line in lines):
        return

    file_dir = os.path.dirname(filepath)
    include_line = get_include_path(root_dir, file_dir)

    new_lines = []
    inserted = False

    for line in lines:
        new_lines.append(line)
        if not inserted and PRAGMA_ONCE in line:
            new_lines.append(include_line)
            inserted = True

    if inserted:
        print(f"Updated: {filepath}")
        with open(filepath, 'w', encoding='utf-8') as f:
            f.writelines(new_lines)

def main():
    root_dir = os.getcwd()

    for dirpath, _, filenames in os.walk(root_dir):
        for filename in filenames:
            if filename.endswith('.hpp'):
                filepath = os.path.join(dirpath, filename)
                process_file(filepath, root_dir)

if __name__ == "__main__":
    main()