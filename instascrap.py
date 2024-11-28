import os

from instagrapi import Client
from pathlib import Path

#@TODO: Add username and password
ACCOUNT_USERNAME = os.environ.get("IG_USERNAME")
ACCOUNT_PASSWORD = os.environ.get("IG_PASSWORD")


def main(username: str, amount: int = 5) -> dict:
    """
    Download all medias from instagram profile
    """
    amount = int(amount)
    cl = Client()
    cl.login(ACCOUNT_USERNAME, ACCOUNT_PASSWORD)
    user_id = cl.user_id_from_username(username)
    medias = cl.user_medias(user_id)
    result = {}
    i = 0
    folder_path = Path(username)
    folder_path.mkdir(exist_ok=True)
    c_content = "Clay_String image_names[] = {\n"
    arr_len = len(medias)
    for m in medias:
        # Add next line in if for testing
        # i >= amount or 
        if m.code == "CLuxe4apA9a" or m.code == "CLuxXB7poUg" or m.code == "CLuxSDTpuIC" or m.media_type != 1:
            continue
        if m.code == "CErOnLfJgDN":
            break
        info = cl.media_info(m.pk)
        paths = []
        if m.media_type == 1:
            image_url = m.thumbnail_url
            file_name = f"{m.code}"
            file_path = folder_path / file_name
            c_content += f"\tCLAY_STRING(IMG_PATH\"{m.code}.jpg\")"
            if not os.path.exists(file_path.with_suffix(".jpg")):
                cl.photo_download_by_url(image_url, file_name, folder_path)
                print(f"Downloaded: {file_path}")
            else:
                print(f"{file_path} already exists")
        # elif m.media_type == 2 and m.product_type == "feed":
        #     # Video
        #     paths.append(cl.video_download(m.pk))
        result[m.pk] = paths
        print(f"http://instagram.com/p/{m.code}/", paths)
        i += 1
        if i != arr_len:
            c_content += ",\n"
        else:
            c_content += "\n"
    c_content += "};\n"
    c_content += f"#define NUM_IMGS {i}\n"
    with open("insta_images.c", 'w') as file:
        file.write(c_content)
    return result


if __name__ == "__main__":
    username = "kri_ookee"
    amount = 1
    main(username, amount)
