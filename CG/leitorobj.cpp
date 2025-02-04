#include "leitorobj.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

bool OBJFileReader::readOBJ(const QString &filename, QVector<Ponto3D> &vertices, QVector<Face> &faces) {
    std::ifstream file(filename.toStdString());
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << filename.toStdString() << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            double x, y, z;
            if (!(iss >> x >> y >> z)) {
                std::cerr << "Erro ao ler vértice na linha: " << line << std::endl;
                continue;
            }
            vertices.append(Ponto3D(x, y, z));
        } else if (prefix == "f") {
            Face face;
            std::string vertexData;

            // Processar apenas os índices antes de um comentário
            size_t commentPos = line.find('#');
            if (commentPos != std::string::npos) {
                line = line.substr(0, commentPos); // Remove comentários
            }
            std::istringstream faceStream(line);

            //Ignorar o prefixo
            faceStream >> prefix;

            //Processar índices dos vértices
            while (faceStream >> vertexData) {
                size_t pos = vertexData.find('/');
                if (pos != std::string::npos)
                    vertexData = vertexData.substr(0, pos); // Apenas índice do vértice

                try {
                    face.indices.append(std::stoi(vertexData) - 1);
                } catch (const std::invalid_argument &e) {
                    std::cerr << "Erro ao converter índice na linha: " << line << std::endl;
                    break;
                } catch (const std::out_of_range &e) {
                    std::cerr << "Índice fora do alcance na linha: " << line << std::endl;
                    break;
                }
            }
            if (!face.indices.isEmpty())
                faces.append(face);
        }
    }

    file.close();

    std::cout << "Vertices carregados: " << vertices.size() << std::endl;
    //std::cout << "Faces carregadas: " << faces.size() << std::endl;
    return true;
}

Matriz OBJFileReader::lerMatriz(const QString &filename, const QString &nomeObjeto) {
    QVector<Ponto3D> vertices;
    QVector<Face> faces;

    if (!readOBJ(filename, vertices, faces)) {
        std::cerr << "Falha ao carregar o arquivo OBJ: " << filename.toStdString() << std::endl;
        return Matriz({}, {}, {}, nomeObjeto);
    }

    //Construir arestas a partir das faces (opcional, se necessário)
    QVector<Aresta> arestas;
    for (const auto &face : faces) {
        for (int i = 0; i < face.indices.size(); ++i) {
            int p1 = face.indices[i];
            int p2 = face.indices[(i + 1) % face.indices.size()];
            arestas.append(Aresta(p1, p2));
        }
    }

    return Matriz(vertices, arestas, faces, nomeObjeto);
}

OBJFileReader::Objeto OBJFileReader::LerArquivo(const QString& caminho) {
    OBJFileReader::Objeto objeto;
    QFile arquivo(caminho);
    if (!arquivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erro ao abrir o arquivo OBJ.";
        return objeto;
    }

    QTextStream stream(&arquivo);
    QVector<Ponto3D> pontos; // Vetor de Ponto3D
    QVector<QPair<int, int>> arestas;

    while (!stream.atEnd()) {
        QString linha = stream.readLine();
        QStringList tokens = linha.split(" ");
        if (tokens[0] == "v") {
            // Adiciona um vértice 3D
            float x = tokens[1].toFloat();
            float y = tokens[2].toFloat();
            float z = tokens[3].toFloat();
            pontos.append(Ponto3D(x, y, z));
        } else if (tokens[0] == "f") {
            // Adiciona uma aresta
            for (int i = 1; i < tokens.size(); ++i) {
                int start = tokens[i].toInt() - 1;
                int end = tokens[(i % tokens.size()) + 1].toInt() - 1;
                arestas.append(qMakePair(start, end));
            }
        }
    }

    objeto.pontos = pontos; // Agora pode atribuir diretamente
    objeto.arestas = arestas;
    return objeto;
}
