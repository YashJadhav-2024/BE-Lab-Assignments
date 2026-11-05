# Assignment 5: K-Means Clustering on Sales Data
# Aim:
# Apply K-Means clustering on sales_data_sample.csv and determine a suitable
# number of clusters using the Elbow Method.
#
# K-Means is an UNSUPERVISED machine-learning algorithm:
# - It groups similar data points into K clusters.
# - It does not require a target/output column.
# - Each cluster is represented by its centroid (the mean of its data points).
#
# This notebook's supplied code implements K-Means clustering.
# Although the assignment statement mentions hierarchical clustering too,
# no hierarchical-clustering code is present in the supplied notebook.

import pandas as pd
import matplotlib.pyplot as plt

# pandas is used to load and manipulate the dataset.
# matplotlib is used to display the Elbow Method graph.

# Load the sales dataset from the CSV file.
# 'unicode_escape' helps read the file if it contains unusual encoded characters.
df = pd.read_csv('5-sales_data_sample.csv', encoding="unicode_escape")

# Display the dataset to inspect its rows and columns.
df

# Remove rows containing missing values (NaN).
# K-Means cannot directly work with missing feature values.
df = df.dropna()

# Display or inspect the cleaned dataset if required.
df

# Select only the numerical columns used to create clusters.
# SALES             = total sales amount
# QUANTITYORDERED   = quantity of products ordered
# PRICEEACH         = price of each product
#
# X contains the input features for K-Means.
# We do not use a target column because K-Means is unsupervised.
X = df[['SALES', 'QUANTITYORDERED', 'PRICEEACH']]

from sklearn.preprocessing import StandardScaler

# Standardization puts features on a comparable scale.
# It transforms each feature so it has approximately:
# mean = 0 and standard deviation = 1.
#
# This is important because SALES may have much larger values than
# QUANTITYORDERED or PRICEEACH. Without scaling, large-valued features
# could dominate the distance calculation used by K-Means.
scaler = StandardScaler()

# Learn the scaling values from X and transform the feature data.
X_scaled = scaler.fit_transform(X)

from sklearn.cluster import KMeans

# ELBOW METHOD:
# The Elbow Method helps select a suitable number of clusters (K).
# We try K values from 1 to 10 and calculate the inertia for each model.
#
# INERTIA / WCSS (Within-Cluster Sum of Squares):
# It is the sum of squared distances between each data point and
# the centroid of the cluster to which that point belongs.
#
# WCSS = sum over clusters of sum over points in a cluster
#        of (distance between point and its cluster centroid)^2
#
# Lower inertia means points are closer to their assigned centroids.
# Inertia normally decreases as K increases, because more clusters
# can fit the data more closely.
#
# The best K is often near the 'elbow': the point where the decrease
# in inertia starts becoming much smaller (diminishing returns).

inertia = []             # Stores inertia for each tested K
K = range(1, 11)         # Test cluster counts from 1 through 10

for k in K:
    # Create a K-Means model with k clusters.
    # random_state=42 makes the random initialization reproducible.
    kmeans = KMeans(n_clusters=k, random_state=42)

    # Fit the model using the standardized feature data.
    kmeans.fit(X_scaled)

    # Store the model's inertia (WCSS).
    inertia.append(kmeans.inertia_)

# Plot the Elbow Method curve: number of clusters (K) vs inertia (WCSS).
plt.figure(figsize=(8, 6))

# 'bo-' means blue circle markers connected by lines.
plt.plot(K, inertia, 'bo-')

# Label both axes so the graph is easy to interpret.
plt.xlabel('Number of clusters (k)')
plt.ylabel('Inertia')

# Add a title and display the graph.
plt.title('Elbow Method for Optimal k')
plt.show()

# Viva point:
# Look for the bend/elbow in the curve. Before the elbow, adding clusters
# reduces inertia significantly. After the elbow, the improvement is smaller.
# The exact elbow should be selected by inspecting the generated graph.

# Select the number of clusters based on the elbow graph.
# The original notebook uses K = 4 as an example choice.
# Change this value if the elbow in your generated graph suggests another K.
optimal_k = 4

# Create the final K-Means model using the selected number of clusters.
kmeans = KMeans(n_clusters=optimal_k, random_state=42)

# fit_predict() trains the model and returns a cluster label for every row.
# These labels are stored in a new column named 'Cluster'.
df['Cluster'] = kmeans.fit_predict(X_scaled)

# Display the selected features along with their assigned cluster.
# Cluster labels are numbers (0, 1, 2, ...); they are group identifiers,
# not rankings or class names.
df[['SALES', 'QUANTITYORDERED', 'PRICEEACH', 'Cluster']]
