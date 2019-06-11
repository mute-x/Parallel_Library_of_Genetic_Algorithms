import sys
import glob
import subprocess
import os
import imageio


def run_cpp_visualization(cpp_visualizator_path, in_file_path, out_filename):
    r = subprocess.run(['./{}'.format(cpp_visualizator_path), in_file_path, out_filename])
    if isinstance(r, subprocess.CalledProcessError):
        print('Something gone wrong with running')
        return False
    else:
        return True


def get_all_visualized_filename(out_filename):
    begin = out_filename.split('.')
    try:
        end = begin[-1]
        begin = begin[0]
    except IndexError:
        print("Something wrong with finding visualized files")
        return False

    return glob.glob('{}*.{}'.format(begin, end))


def create_gif(out_filenames, duration):
    images = []
    for filename in out_filenames:
        images.append(imageio.imread(filename))
    output_file = 'new_result.gif'
    imageio.mimsave(output_file, images, duration=duration)


def clean_used_out_filenames(filenames):
    for filename in filenames:
        os.remove(filename)


def main(cpp_visualizator_path, in_file_path, out_filename):
    if not run_cpp_visualization(cpp_visualizator_path, in_file_path, out_filename):
        print("Error in running")
        return -1

    out_vis_filenames = get_all_visualized_filename(out_filename)
    if not out_vis_filenames:
        print("Error in finding out files.")

    # SET HERE DURATION OF EACH FRAME
    create_gif(out_vis_filenames, 0.5)

    clean_used_out_filenames(out_vis_filenames)


if __name__ == "__main__":
    main('../cmake-build-debug/VISUALIZATION', '../data/example.txt', 'iteration.png')
