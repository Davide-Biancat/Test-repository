#-------------------------------------------------
#
# Project created by QtCreator 2016-04-26T08:54:54
#
#-------------------------------------------------

QT       += core gui serialport printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        arduinoreader.cpp \
        glwidget.cpp \
        logo.cpp \
        worker.cpp \
        libs/QCustomPlot/qcustomplot.cpp \
  #  debug/moc_arduinoreader.cpp \
  #  debug/moc_glwidget.cpp \
  #  debug/moc_mainwindow.cpp \
  #  debug/moc_qcustomplot.cpp \
  #  debug/moc_worker.cpp \

INCLUDEPATH += "$$_PRO_FILE_PWD_/libs/QCustomPlot"

HEADERS  += mainwindow.h \
    arduinoreader.h \
    libs/QCustomPlot/qcustomplot.h \
    glwidget.h \
    logo.h \
    worker.h \
    libs/Eigen/src/Cholesky/LDLT.h \
    libs/Eigen/src/Cholesky/LLT.h \
    libs/Eigen/src/Cholesky/LLT_MKL.h \
    libs/Eigen/src/CholmodSupport/CholmodSupport.h \
    libs/Eigen/src/Core/arch/AltiVec/Complex.h \
    libs/Eigen/src/Core/arch/AltiVec/PacketMath.h \
    libs/Eigen/src/Core/arch/Default/Settings.h \
    libs/Eigen/src/Core/arch/NEON/Complex.h \
    libs/Eigen/src/Core/arch/NEON/PacketMath.h \
    libs/Eigen/src/Core/arch/SSE/Complex.h \
    libs/Eigen/src/Core/arch/SSE/MathFunctions.h \
    libs/Eigen/src/Core/arch/SSE/PacketMath.h \
    libs/Eigen/src/Core/products/CoeffBasedProduct.h \
    libs/Eigen/src/Core/products/GeneralBlockPanelKernel.h \
    libs/Eigen/src/Core/products/GeneralMatrixMatrix.h \
    libs/Eigen/src/Core/products/GeneralMatrixMatrix_MKL.h \
    libs/Eigen/src/Core/products/GeneralMatrixMatrixTriangular.h \
    libs/Eigen/src/Core/products/GeneralMatrixMatrixTriangular_MKL.h \
    libs/Eigen/src/Core/products/GeneralMatrixVector.h \
    libs/Eigen/src/Core/products/GeneralMatrixVector_MKL.h \
    libs/Eigen/src/Core/products/Parallelizer.h \
    libs/Eigen/src/Core/products/SelfadjointMatrixMatrix.h \
    libs/Eigen/src/Core/products/SelfadjointMatrixMatrix_MKL.h \
    libs/Eigen/src/Core/products/SelfadjointMatrixVector.h \
    libs/Eigen/src/Core/products/SelfadjointMatrixVector_MKL.h \
    libs/Eigen/src/Core/products/SelfadjointProduct.h \
    libs/Eigen/src/Core/products/SelfadjointRank2Update.h \
    libs/Eigen/src/Core/products/TriangularMatrixMatrix.h \
    libs/Eigen/src/Core/products/TriangularMatrixMatrix_MKL.h \
    libs/Eigen/src/Core/products/TriangularMatrixVector.h \
    libs/Eigen/src/Core/products/TriangularMatrixVector_MKL.h \
    libs/Eigen/src/Core/products/TriangularSolverMatrix.h \
    libs/Eigen/src/Core/products/TriangularSolverMatrix_MKL.h \
    libs/Eigen/src/Core/products/TriangularSolverVector.h \
    libs/Eigen/src/Core/util/BlasUtil.h \
    libs/Eigen/src/Core/util/Constants.h \
    libs/Eigen/src/Core/util/DisableStupidWarnings.h \
    libs/Eigen/src/Core/util/ForwardDeclarations.h \
    libs/Eigen/src/Core/util/Macros.h \
    libs/Eigen/src/Core/util/Memory.h \
    libs/Eigen/src/Core/util/Meta.h \
    libs/Eigen/src/Core/util/MKL_support.h \
    libs/Eigen/src/Core/util/NonMPL2.h \
    libs/Eigen/src/Core/util/ReenableStupidWarnings.h \
    libs/Eigen/src/Core/util/StaticAssert.h \
    libs/Eigen/src/Core/util/XprHelper.h \
    libs/Eigen/src/Core/Array.h \
    libs/Eigen/src/Core/ArrayBase.h \
    libs/Eigen/src/Core/ArrayWrapper.h \
    libs/Eigen/src/Core/Assign.h \
    libs/Eigen/src/Core/Assign_MKL.h \
    libs/Eigen/src/Core/BandMatrix.h \
    libs/Eigen/src/Core/Block.h \
    libs/Eigen/src/Core/BooleanRedux.h \
    libs/Eigen/src/Core/CommaInitializer.h \
    libs/Eigen/src/Core/CoreIterators.h \
    libs/Eigen/src/Core/CwiseBinaryOp.h \
    libs/Eigen/src/Core/CwiseNullaryOp.h \
    libs/Eigen/src/Core/CwiseUnaryOp.h \
    libs/Eigen/src/Core/CwiseUnaryView.h \
    libs/Eigen/src/Core/DenseBase.h \
    libs/Eigen/src/Core/DenseCoeffsBase.h \
    libs/Eigen/src/Core/DenseStorage.h \
    libs/Eigen/src/Core/Diagonal.h \
    libs/Eigen/src/Core/DiagonalMatrix.h \
    libs/Eigen/src/Core/DiagonalProduct.h \
    libs/Eigen/src/Core/Dot.h \
    libs/Eigen/src/Core/EigenBase.h \
    libs/Eigen/src/Core/Flagged.h \
    libs/Eigen/src/Core/ForceAlignedAccess.h \
    libs/Eigen/src/Core/Functors.h \
    libs/Eigen/src/Core/Fuzzy.h \
    libs/Eigen/src/Core/GeneralProduct.h \
    libs/Eigen/src/Core/GenericPacketMath.h \
    libs/Eigen/src/Core/GlobalFunctions.h \
    libs/Eigen/src/Core/IO.h \
    libs/Eigen/src/Core/Map.h \
    libs/Eigen/src/Core/MapBase.h \
    libs/Eigen/src/Core/MathFunctions.h \
    libs/Eigen/src/Core/Matrix.h \
    libs/Eigen/src/Core/MatrixBase.h \
    libs/Eigen/src/Core/NestByValue.h \
    libs/Eigen/src/Core/NoAlias.h \
    libs/Eigen/src/Core/NumTraits.h \
    libs/Eigen/src/Core/PermutationMatrix.h \
    libs/Eigen/src/Core/PlainObjectBase.h \
    libs/Eigen/src/Core/ProductBase.h \
    libs/Eigen/src/Core/Random.h \
    libs/Eigen/src/Core/Redux.h \
    libs/Eigen/src/Core/Ref.h \
    libs/Eigen/src/Core/Replicate.h \
    libs/Eigen/src/Core/ReturnByValue.h \
    libs/Eigen/src/Core/Reverse.h \
    libs/Eigen/src/Core/Select.h \
    libs/Eigen/src/Core/SelfAdjointView.h \
    libs/Eigen/src/Core/SelfCwiseBinaryOp.h \
    libs/Eigen/src/Core/SolveTriangular.h \
    libs/Eigen/src/Core/StableNorm.h \
    libs/Eigen/src/Core/Stride.h \
    libs/Eigen/src/Core/Swap.h \
    libs/Eigen/src/Core/Transpose.h \
    libs/Eigen/src/Core/Transpositions.h \
    libs/Eigen/src/Core/TriangularMatrix.h \
    libs/Eigen/src/Core/VectorBlock.h \
    libs/Eigen/src/Core/VectorwiseOp.h \
    libs/Eigen/src/Core/Visitor.h \
    libs/Eigen/src/Eigen2Support/Geometry/AlignedBox.h \
    libs/Eigen/src/Eigen2Support/Geometry/All.h \
    libs/Eigen/src/Eigen2Support/Geometry/AngleAxis.h \
    libs/Eigen/src/Eigen2Support/Geometry/Hyperplane.h \
    libs/Eigen/src/Eigen2Support/Geometry/ParametrizedLine.h \
    libs/Eigen/src/Eigen2Support/Geometry/Quaternion.h \
    libs/Eigen/src/Eigen2Support/Geometry/Rotation2D.h \
    libs/Eigen/src/Eigen2Support/Geometry/RotationBase.h \
    libs/Eigen/src/Eigen2Support/Geometry/Scaling.h \
    libs/Eigen/src/Eigen2Support/Geometry/Transform.h \
    libs/Eigen/src/Eigen2Support/Geometry/Translation.h \
    libs/Eigen/src/Eigen2Support/Block.h \
    libs/Eigen/src/Eigen2Support/Cwise.h \
    libs/Eigen/src/Eigen2Support/CwiseOperators.h \
    libs/Eigen/src/Eigen2Support/Lazy.h \
    libs/Eigen/src/Eigen2Support/LeastSquares.h \
    libs/Eigen/src/Eigen2Support/LU.h \
    libs/Eigen/src/Eigen2Support/Macros.h \
    libs/Eigen/src/Eigen2Support/MathFunctions.h \
    libs/Eigen/src/Eigen2Support/Memory.h \
    libs/Eigen/src/Eigen2Support/Meta.h \
    libs/Eigen/src/Eigen2Support/Minor.h \
    libs/Eigen/src/Eigen2Support/QR.h \
    libs/Eigen/src/Eigen2Support/SVD.h \
    libs/Eigen/src/Eigen2Support/TriangularSolver.h \
    libs/Eigen/src/Eigen2Support/VectorBlock.h \
    libs/Eigen/src/Eigenvalues/ComplexEigenSolver.h \
    libs/Eigen/src/Eigenvalues/ComplexSchur.h \
    libs/Eigen/src/Eigenvalues/ComplexSchur_MKL.h \
    libs/Eigen/src/Eigenvalues/EigenSolver.h \
    libs/Eigen/src/Eigenvalues/GeneralizedEigenSolver.h \
    libs/Eigen/src/Eigenvalues/GeneralizedSelfAdjointEigenSolver.h \
    libs/Eigen/src/Eigenvalues/HessenbergDecomposition.h \
    libs/Eigen/src/Eigenvalues/MatrixBaseEigenvalues.h \
    libs/Eigen/src/Eigenvalues/RealQZ.h \
    libs/Eigen/src/Eigenvalues/RealSchur.h \
    libs/Eigen/src/Eigenvalues/RealSchur_MKL.h \
    libs/Eigen/src/Eigenvalues/SelfAdjointEigenSolver.h \
    libs/Eigen/src/Eigenvalues/SelfAdjointEigenSolver_MKL.h \
    libs/Eigen/src/Eigenvalues/Tridiagonalization.h \
    libs/Eigen/src/Geometry/arch/Geometry_SSE.h \
    libs/Eigen/src/Geometry/AlignedBox.h \
    libs/Eigen/src/Geometry/AngleAxis.h \
    libs/Eigen/src/Geometry/EulerAngles.h \
    libs/Eigen/src/Geometry/Homogeneous.h \
    libs/Eigen/src/Geometry/Hyperplane.h \
    libs/Eigen/src/Geometry/OrthoMethods.h \
    libs/Eigen/src/Geometry/ParametrizedLine.h \
    libs/Eigen/src/Geometry/Quaternion.h \
    libs/Eigen/src/Geometry/Rotation2D.h \
    libs/Eigen/src/Geometry/RotationBase.h \
    libs/Eigen/src/Geometry/Scaling.h \
    libs/Eigen/src/Geometry/Transform.h \
    libs/Eigen/src/Geometry/Translation.h \
    libs/Eigen/src/Geometry/Umeyama.h \
    libs/Eigen/src/Householder/BlockHouseholder.h \
    libs/Eigen/src/Householder/Householder.h \
    libs/Eigen/src/Householder/HouseholderSequence.h \
    libs/Eigen/src/IterativeLinearSolvers/BasicPreconditioners.h \
    libs/Eigen/src/IterativeLinearSolvers/BiCGSTAB.h \
    libs/Eigen/src/IterativeLinearSolvers/ConjugateGradient.h \
    libs/Eigen/src/IterativeLinearSolvers/IncompleteLUT.h \
    libs/Eigen/src/IterativeLinearSolvers/IterativeSolverBase.h \
    libs/Eigen/src/Jacobi/Jacobi.h \
    libs/Eigen/src/LU/arch/Inverse_SSE.h \
    libs/Eigen/src/LU/Determinant.h \
    libs/Eigen/src/LU/FullPivLU.h \
    libs/Eigen/src/LU/Inverse.h \
    libs/Eigen/src/LU/PartialPivLU.h \
    libs/Eigen/src/LU/PartialPivLU_MKL.h \
    libs/Eigen/src/MetisSupport/MetisSupport.h \
    libs/Eigen/src/misc/blas.h \
    libs/Eigen/src/misc/Image.h \
    libs/Eigen/src/misc/Kernel.h \
    libs/Eigen/src/misc/Solve.h \
    libs/Eigen/src/misc/SparseSolve.h \
    libs/Eigen/src/OrderingMethods/Amd.h \
    libs/Eigen/src/OrderingMethods/Eigen_Colamd.h \
    libs/Eigen/src/OrderingMethods/Ordering.h \
    libs/Eigen/src/PardisoSupport/PardisoSupport.h \
    libs/Eigen/src/PaStiXSupport/PaStiXSupport.h \
    libs/Eigen/src/plugins/ArrayCwiseBinaryOps.h \
    libs/Eigen/src/plugins/ArrayCwiseUnaryOps.h \
    libs/Eigen/src/plugins/BlockMethods.h \
    libs/Eigen/src/plugins/CommonCwiseBinaryOps.h \
    libs/Eigen/src/plugins/CommonCwiseUnaryOps.h \
    libs/Eigen/src/plugins/MatrixCwiseBinaryOps.h \
    libs/Eigen/src/plugins/MatrixCwiseUnaryOps.h \
    libs/Eigen/src/QR/ColPivHouseholderQR.h \
    libs/Eigen/src/QR/ColPivHouseholderQR_MKL.h \
    libs/Eigen/src/QR/FullPivHouseholderQR.h \
    libs/Eigen/src/QR/HouseholderQR.h \
    libs/Eigen/src/QR/HouseholderQR_MKL.h \
    libs/Eigen/src/SparseCholesky/SimplicialCholesky.h \
    libs/Eigen/src/SparseCholesky/SimplicialCholesky_impl.h \
    libs/Eigen/src/SparseCore/AmbiVector.h \
    libs/Eigen/src/SparseCore/CompressedStorage.h \
    libs/Eigen/src/SparseCore/ConservativeSparseSparseProduct.h \
    libs/Eigen/src/SparseCore/MappedSparseMatrix.h \
    libs/Eigen/src/SparseCore/SparseBlock.h \
    libs/Eigen/src/SparseCore/SparseColEtree.h \
    libs/Eigen/src/SparseCore/SparseCwiseBinaryOp.h \
    libs/Eigen/src/SparseCore/SparseCwiseUnaryOp.h \
    libs/Eigen/src/SparseCore/SparseDenseProduct.h \
    libs/Eigen/src/SparseCore/SparseDiagonalProduct.h \
    libs/Eigen/src/SparseCore/SparseDot.h \
    libs/Eigen/src/SparseCore/SparseFuzzy.h \
    libs/Eigen/src/SparseCore/SparseMatrix.h \
    libs/Eigen/src/SparseCore/SparseMatrixBase.h \
    libs/Eigen/src/SparseCore/SparsePermutation.h \
    libs/Eigen/src/SparseCore/SparseProduct.h \
    libs/Eigen/src/SparseCore/SparseRedux.h \
    libs/Eigen/src/SparseCore/SparseSelfAdjointView.h \
    libs/Eigen/src/SparseCore/SparseSparseProductWithPruning.h \
    libs/Eigen/src/SparseCore/SparseTranspose.h \
    libs/Eigen/src/SparseCore/SparseTriangularView.h \
    libs/Eigen/src/SparseCore/SparseUtil.h \
    libs/Eigen/src/SparseCore/SparseVector.h \
    libs/Eigen/src/SparseCore/SparseView.h \
    libs/Eigen/src/SparseCore/TriangularSolver.h \
    libs/Eigen/src/SparseLU/SparseLU.h \
    libs/Eigen/src/SparseLU/SparseLU_column_bmod.h \
    libs/Eigen/src/SparseLU/SparseLU_column_dfs.h \
    libs/Eigen/src/SparseLU/SparseLU_copy_to_ucol.h \
    libs/Eigen/src/SparseLU/SparseLU_gemm_kernel.h \
    libs/Eigen/src/SparseLU/SparseLU_heap_relax_snode.h \
    libs/Eigen/src/SparseLU/SparseLU_kernel_bmod.h \
    libs/Eigen/src/SparseLU/SparseLU_Memory.h \
    libs/Eigen/src/SparseLU/SparseLU_panel_bmod.h \
    libs/Eigen/src/SparseLU/SparseLU_panel_dfs.h \
    libs/Eigen/src/SparseLU/SparseLU_pivotL.h \
    libs/Eigen/src/SparseLU/SparseLU_pruneL.h \
    libs/Eigen/src/SparseLU/SparseLU_relax_snode.h \
    libs/Eigen/src/SparseLU/SparseLU_Structs.h \
    libs/Eigen/src/SparseLU/SparseLU_SupernodalMatrix.h \
    libs/Eigen/src/SparseLU/SparseLU_Utils.h \
    libs/Eigen/src/SparseLU/SparseLUImpl.h \
    libs/Eigen/src/SparseQR/SparseQR.h \
    libs/Eigen/src/SPQRSupport/SuiteSparseQRSupport.h \
    libs/Eigen/src/StlSupport/details.h \
    libs/Eigen/src/StlSupport/StdDeque.h \
    libs/Eigen/src/StlSupport/StdList.h \
    libs/Eigen/src/StlSupport/StdVector.h \
    libs/Eigen/src/SuperLUSupport/SuperLUSupport.h \
    libs/Eigen/src/SVD/JacobiSVD.h \
    libs/Eigen/src/SVD/JacobiSVD_MKL.h \
    libs/Eigen/src/SVD/UpperBidiagonalization.h \
    libs/Eigen/src/UmfPackSupport/UmfPackSupport.h \

FORMS    += mainwindow.ui

#DISTFILES += \
 #   object_script.untitled1.Debug \
  #  object_script.untitled1.Release
