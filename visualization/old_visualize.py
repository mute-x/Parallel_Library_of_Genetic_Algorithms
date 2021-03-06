import matplotlib.pyplot as plt
import imageio
import numpy as np
import os
import sys
plt.rcParams.update({'figure.max_open_warning': 0})


def parse_file(in_filename):
    def get_tuple(str_tuple):
        str_tuple = str_tuple.strip().strip(')').strip('(')
        first_value, second_value = str_tuple.split(',')
        first_value = int(first_value.strip())
        second_value = int(second_value.strip())
        return (first_value, second_value)

    result = dict()
    with open(in_filename, 'r') as file:
        data = file.readlines()
        line = data[0].strip('\n').split()
        result['number_of_items'] = int(line[0])
        result['number_of_iterations'] = int(line[1])
        line = data[1].strip('\n').split()
        result['x'] = (int(line[0]), int(line[1]))
        result['y'] = (int(line[2]), int(line[3]))
        result['function'] = [[float(item) for item in line.strip('\n').split()]
                              for line in data[2: result['x'][1] - result['x'][0] + 3]]
        result['moving'] = [[get_tuple(item) for item in line.strip('\n').strip().split(')')[:-1]] for line in data[result['x'][1] - result['x'][0] + 3:
                                                result['x'][1] - result['x'][0] + 5 + result['number_of_iterations']]]
    return result


def plot_result(results):
    def plot_current_iteration(iteration, items):
        fig, ax = plt.subplots()
        data1 = []
        for i in range(len(data)):
            data1.append([row[i] for row in data])

        heatmap = ax.pcolor(data1, cmap=plt.cm.Blues)

        # put the major ticks at the middle of each cell
        ax.set_xticks(np.arange(data.shape[0]) + 0.5, minor=False)
        ax.set_yticks(np.arange(data.shape[1]) + 0.5, minor=False)

        ax.set_xticklabels(row_labels, minor=False)
        ax.set_yticklabels(column_labels, minor=False)

        max_current_value = -10000000
        for item in items:
            try:
                if data[item[0] - results['x'][0]][item[1] - results['y'][0]] > max_current_value:
                    max_current_value = data[item[0] - results['y'][0]][item[1] - results['y'][0]]
            except IndexError:
                print(item)
            circ = plt.Circle((item[0] + 0.5 - results['x'][0], item[1] + 0.5 - results['y'][0]), radius=0.4, color='r')
            ax.add_patch(circ)

        plt.text(0.05, 1.1,
                     "Current iteration: {}".format(iteration),
                     transform=plt.gca().transAxes)

        plt.text(0.05, 1.025,
                     "Best current value: {}".format(max_current_value),
                     transform=plt.gca().transAxes)

        fig.savefig('{}.png'.format(iteration))

    def create_gif(filenames, duration):
        images = []
        for filename in filenames:
            images.append(imageio.imread(filename))
        output_file = 'gif_pictures/parallel_library_of_genetic_algorithms/new_result.gif'
        imageio.mimsave(output_file, images, duration=duration)

    column_labels = list(range(results['y'][0], results['y'][1] + 1))
    row_labels = list(range(results['x'][0], results['x'][1] + 1))

    data = np.array(results['function'])
    for i in range(1, results['number_of_iterations'] + 1):
        plot_current_iteration(i, results['moving'][i - 1])

    create_gif(['{}.png'.format(i) for i in range(1, results['number_of_iterations'] + 1)], 0.5)
    for i in range(1, results['number_of_iterations'] + 1):
        os.remove("{}.png".format(i))


def main(in_filename):
    results = parse_file(in_filename)
    plot_result(results)


if __name__ == "__main__":
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    else:
        filename = 'example.txt'
    main('../data/{}'.format(filename))
