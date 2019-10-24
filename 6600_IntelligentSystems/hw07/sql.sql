_____ Parallel stuff for Riley _______
            WorkerEnvelope rec;
            MPI_Recv(&rec, sizeof(WorkerEnvelope), MPI_BYTE, completedProcess, 0, MCW, MPI_STATUS_IGNORE);

            int iOffset = (rec.chunkId % chunksInARow) * CHUNK_SIZE;
            int jOffset = ((rec.chunkId / chunksInARow) * CHUNK_SIZE);
            int iMax = std::min(iOffset + CHUNK_SIZE, IMAGE_SIZE);
            int jMax = std::min(jOffset + CHUNK_SIZE, IMAGE_SIZE);
            for (int i = iOffset; i < iMax; ++i) {
                for (int j = jOffset; j < jMax; ++j) {
                    image[i][j] = rec.data[i-iOffset][j-jOffset];
                    if(image[i][j] > max){
                        max = image[i][j];
                    }
                    if(image[i][j] < min){
                        min = image[i][j];
                    }
                }
            }
