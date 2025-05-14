import os

from pathlib import Path
import shutil


def main(directory: str) -> dict:
    """
    Generate all medias to c
    """
    medias = [f for f in os.listdir(directory) if os.path.isfile(os.path.join(directory, f))]
    result = {}
    i = 0
    folder_path = Path("images/insta")
    folder_path.mkdir(exist_ok=True)
    c_content = "Clay_String image_names[] = {\n"
    arr_len = len(medias)
    for m in medias:
        paths = []
        file_name = f"{m}"
        m = m.split('.')[0]
        file_path = folder_path / file_name
        origin_path = Path(directory) / file_name
        c_content += f"\tCLAY_STRING(IMG_PATH\"{m}.jpg\")"
        if not os.path.exists(file_path.with_suffix(".jpg")):
            print(f"Downloaded: {file_path} from {origin_path}")
            shutil.copy(origin_path,folder_path)
        else:
            print(f"{file_path} already exists")
        result[m] = paths
        i += 1
        if i != arr_len:
            c_content += ",\n"
        else:
            c_content += "\n"
    c_content += "};\n"
    c_content += f"#define NUM_IMGS {i}\n"
    with open("insta_images.c", 'w',encoding='utf-8') as file:
        file.write(c_content)
    return result


if __name__ == "__main__":
    FOLDERNAME = "kri_ookee"
    main(FOLDERNAME)
