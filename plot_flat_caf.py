import uproot
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys

# Open the ROOT file and access the TTree
caf_file = uproot.open(sys.argv[1])
caf_tree = caf_file['cafTree']

# Create an empty dictionary to store branch data
caf_data_dict = {}

# Iterate over the branch names in the TTree
for branch_name in caf_tree.keys():
    # Use branch_name as the key and fetch the data using .array()
    caf_data_dict[branch_name] = caf_tree[branch_name].array(library="np")

# Create a Pandas DataFrame from the dictionary
df = pd.DataFrame(caf_data_dict)

#unpack reco vertex x
flattened_data_reco = df['rec.common.ixn.dlp.vtx.x'].apply(lambda x: [val for val in x if not np.isnan(val)]).tolist()
flattened_data_reco = [val for sublist in flattened_data_reco for val in sublist]

#unpack truth vertex x
flattened_data_truth = df['rec.mc.nu.vtx.x'].apply(lambda x: [val for val in x if not np.isnan(val)]).tolist()
flattened_data_truth = [val for sublist in flattened_data_truth for val in sublist]

plt.hist(flattened_data_reco, bins=100, alpha=0.5, label = 'reco')
plt.hist(flattened_data_truth, bins=100, alpha=0.5, label='truth')
plt.legend()
plt.title('Reco vs True interaction vertex')
plt.ylabel('No. of interactions')
plt.xlabel('Interaction vertex x [cm]')

plt.savefig('flatcaf_reco_vs_truth_ixn_vtx_x.png')
