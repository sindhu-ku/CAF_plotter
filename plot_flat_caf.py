import uproot
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys


def make_df(caf_file):

    caf_tree = caf_file['cafTree']

    # Create an empty dictionary to store branch data
    caf_data_dict = {}

    #Iterate over the branch names in the TTree
    for branch_name in caf_tree.keys():
        # Use branch_name as the key and fetch the data using .array()
        caf_data_dict[branch_name] = caf_tree[branch_name].array(library="np")

    # Create a Pandas DataFrame from the dictionary
    df = pd.DataFrame(caf_data_dict)

    return df

def make_hist(data, bins, range, alpha, label, title, xlabel, ylabel):

    for i, d in enumerate(data):
        print(i)
        plt.hist(data[i], bins=bins, range=range, alpha=alpha, label=label[i])
    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    if(len(data) > 1): plt.legend()
    plt.show()

def plot_stuff(df):

    #unpack reco vertex x
    reco_vtx_x = df['rec.common.ixn.dlp.vtx.x']
    flattened_reco_vtx_x = [val for sublist in reco_vtx_x for val in sublist]

    #unpack truth vertex x
    truth_vtx_x = df['rec.mc.nu.vtx.x']
    flattened_truth_vtx_x = [val for sublist in truth_vtx_x for val in sublist]

    #plot reco and truth vtx x
    make_hist(data=[flattened_reco_vtx_x, flattened_truth_vtx_x], bins=100, range=(-100, 100), alpha=0.5, label=['reco', 'truth'], title='Reco vs True interaction vertex', xlabel='No. of interactions', ylabel='No. of interactions')

    # Unpack pdg values
    pdg = df['rec.common.ixn.dlp.part.dlp.pdg']
    flattened_pdg = [val for sublist in pdg for val in sublist]

    # Unpack reco energy
    reco_energy = df['rec.common.ixn.dlp.part.dlp.E']
    flattened_reco_energy = [val for sublist in reco_energy for val in sublist]

    #make a daatframe with just the two variables
    energy_pdg_dict = {'recoE':flattened_reco_energy, 'pdg':flattened_pdg}
    df_energy_pdg = pd.DataFrame(energy_pdg_dict)

    #apply a muon cut
    df_energy_pdg = df_energy_pdg[df_energy_pdg['pdg'].abs() == 13]

    #Plot the reco energy for muons
    make_hist(data=[df_energy_pdg['recoE']], bins=100, range=(0,1), alpha=0.7,label=[''], title='Reco energy distribution for muons', xlabel='Energy (GeV)', ylabel='No. of reco particles')

def main(argv):
    if (len(sys.argv) <  2):
          print("ERROR: Please give the input file or a list of input files as an argument")
    # Open the ROOT file and access the TTree

    #For one file
    if(sys.argv[1].endswith('root')):
        print("Reading", sys.argv[1])
        caf_file = uproot.open(sys.argv[1])
        df = make_df(caf_file)
        plot_stuff(df)

    #For a list
    elif(sys.argv[1].endswith('list')):
        file_list = open(sys.argv[1], 'r')
        data = []
        df = pd.DataFrame(data)
        for line in file_list:
            print("Reading", line)
            caf_file = uproot.open(line)
            df_temp = make_df(caf_file)
            df = pd.concat([df, df_temp])
        plot_stuff(df)
        
    else:
        print("Error: You can only give root file or list as an input")
        return

if __name__ == "__main__":
  main(sys.argv[1:])
