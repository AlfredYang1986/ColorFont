#-------------------------------------------------
#
# Project created by QtCreator 2017-11-07T14:33:52
#
#-------------------------------------------------

QT  += core gui
QT  += xml
QT 	+= opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ColorFont
TEMPLATE = app


SOURCES += main.cpp\
		glm/detail/glm.cpp \
		cfmainwindow.cpp \
	glm/detail/glm.cpp \
	prevdialog/cfprevdialog.cpp \
	module/fileopt/cffileopt.cpp \
	module/modulemanagement/cfmm.cpp \
	module/basemodules/cfbasemodule.cpp \
    errorhandler/cferrorhandler.cpp \
    module/fftopt/cffftopt.cpp \
    dockwidget/cfeffectdock.cpp \
    dockwidget/shadowwidget/cfshadowwidget.cpp \
    dockwidget/effectwidget/cfeffectwidget.cpp \
    dockwidget/bkgwidget/cfbkgwidget.cpp \
    dockwidget/hangupwidget/cfhangupwidget.cpp \
    dockwidget/fillwidget/cffillwidget.cpp \
    dockwidget/commonwidget/colorbkg/cfcolorbkg.cpp \
    dockwidget/commonwidget/colorbkg/cfcolorpreviewpanel.cpp \
    dockwidget/commonwidget/colorbkg/cfcolorselectpanel.cpp \
    dockwidget/commonwidget/gradientwidget/lineargradientwidget/cflineargradientwidget.cpp \
    dockwidget/commonwidget/gradientwidget/cfgradientwidget.cpp \
    dockwidget/commonwidget/imgwidget/cfimgwidget.cpp \
    dockwidget/borderwidget/cfborderwidget.cpp \
    dockwidget/preparedwidget/cfpreparedwidget.cpp \
    dockwidget/cfresentchardock.cpp \
    operatorwidget/cfoperatorwidget.cpp \
    common/cfpassable.cpp \
    common/funcargs/cfargs.cpp \
    operatorwidget/cfoperatortab.cpp \
    dialog/importdialog/cfimportttfdialog.cpp \
    dialog/importdialog/cfimportindexcell.cpp \
    dialog/previewwidget/cfpreviewwidget.cpp \
    module/openglopt/cfopenglopt.cpp \
    common/pagewidget/PageWidget.cpp \
    module/xmlopt/cfxmlopt.cpp \
    dialog/fftlibprevwidget/cffftlibprevwidget.cpp \
	operatorwidget/cfgllinewidget.cpp \
    module/queryopt/cfqueryopt.cpp

HEADERS  += \
		glm/detail/_features.hpp \
		glm/detail/_fixes.hpp \
		glm/detail/_noise.hpp \
		glm/detail/_swizzle.hpp \
		glm/detail/_swizzle_func.hpp \
		glm/detail/_vectorize.hpp \
		glm/detail/compute_vector_relational.hpp \
		glm/detail/qualifier.hpp \
		glm/detail/setup.hpp \
		glm/detail/type_float.hpp \
		glm/detail/type_gentype.hpp \
		glm/detail/type_half.hpp \
		glm/detail/type_int.hpp \
		glm/detail/type_mat.hpp \
		glm/detail/type_mat2x2.hpp \
		glm/detail/type_mat2x3.hpp \
		glm/detail/type_mat2x4.hpp \
		glm/detail/type_mat3x2.hpp \
		glm/detail/type_mat3x3.hpp \
		glm/detail/type_mat3x4.hpp \
		glm/detail/type_mat4x2.hpp \
		glm/detail/type_mat4x3.hpp \
		glm/detail/type_mat4x4.hpp \
		glm/detail/type_vec.hpp \
		glm/detail/type_vec1.hpp \
		glm/detail/type_vec2.hpp \
		glm/detail/type_vec3.hpp \
		glm/detail/type_vec4.hpp \
		glm/ext/vec1.hpp \
		glm/ext/vector_relational.hpp \
		glm/gtc/bitfield.hpp \
		glm/gtc/color_space.hpp \
		glm/gtc/constants.hpp \
		glm/gtc/epsilon.hpp \
		glm/gtc/integer.hpp \
		glm/gtc/matrix_access.hpp \
		glm/gtc/matrix_integer.hpp \
		glm/gtc/matrix_inverse.hpp \
		glm/gtc/matrix_transform.hpp \
		glm/gtc/noise.hpp \
		glm/gtc/packing.hpp \
		glm/gtc/quaternion.hpp \
		glm/gtc/random.hpp \
		glm/gtc/reciprocal.hpp \
		glm/gtc/round.hpp \
		glm/gtc/type_aligned.hpp \
		glm/gtc/type_precision.hpp \
		glm/gtc/type_ptr.hpp \
		glm/gtc/ulp.hpp \
		glm/gtc/vec1.hpp \
		glm/gtx/associated_min_max.hpp \
		glm/gtx/bit.hpp \
		glm/gtx/closest_point.hpp \
		glm/gtx/color_encoding.hpp \
		glm/gtx/color_space.hpp \
		glm/gtx/color_space_YCoCg.hpp \
		glm/gtx/common.hpp \
		glm/gtx/compatibility.hpp \
		glm/gtx/component_wise.hpp \
		glm/gtx/dual_quaternion.hpp \
		glm/gtx/euler_angles.hpp \
		glm/gtx/extend.hpp \
		glm/gtx/extended_min_max.hpp \
		glm/gtx/exterior_product.hpp \
		glm/gtx/fast_exponential.hpp \
		glm/gtx/fast_square_root.hpp \
		glm/gtx/fast_trigonometry.hpp \
		glm/gtx/functions.hpp \
		glm/gtx/gradient_paint.hpp \
		glm/gtx/handed_coordinate_space.hpp \
		glm/gtx/hash.hpp \
		glm/gtx/integer.hpp \
		glm/gtx/intersect.hpp \
		glm/gtx/io.hpp \
		glm/gtx/log_base.hpp \
		glm/gtx/matrix_cross_product.hpp \
		glm/gtx/matrix_decompose.hpp \
		glm/gtx/matrix_factorisation.hpp \
		glm/gtx/matrix_interpolation.hpp \
		glm/gtx/matrix_major_storage.hpp \
		glm/gtx/matrix_operation.hpp \
		glm/gtx/matrix_query.hpp \
		glm/gtx/matrix_transform_2d.hpp \
		glm/gtx/mixed_product.hpp \
		glm/gtx/norm.hpp \
		glm/gtx/normal.hpp \
		glm/gtx/normalize_dot.hpp \
		glm/gtx/number_precision.hpp \
		glm/gtx/optimum_pow.hpp \
		glm/gtx/orthonormalize.hpp \
		glm/gtx/perpendicular.hpp \
		glm/gtx/polar_coordinates.hpp \
		glm/gtx/projection.hpp \
		glm/gtx/quaternion.hpp \
		glm/gtx/range.hpp \
		glm/gtx/raw_data.hpp \
		glm/gtx/rotate_normalized_axis.hpp \
		glm/gtx/rotate_vector.hpp \
		glm/gtx/scalar_multiplication.hpp \
		glm/gtx/scalar_relational.hpp \
		glm/gtx/spline.hpp \
		glm/gtx/std_based_type.hpp \
		glm/gtx/string_cast.hpp \
		glm/gtx/texture.hpp \
		glm/gtx/transform.hpp \
		glm/gtx/transform2.hpp \
		glm/gtx/type_aligned.hpp \
		glm/gtx/type_trait.hpp \
		glm/gtx/vec_swizzle.hpp \
		glm/gtx/vector_angle.hpp \
		glm/gtx/vector_query.hpp \
		glm/gtx/wrap.hpp \
		glm/simd/common.h \
		glm/simd/exponential.h \
		glm/simd/geometric.h \
		glm/simd/integer.h \
		glm/simd/matrix.h \
		glm/simd/packing.h \
		glm/simd/platform.h \
		glm/simd/trigonometric.h \
		glm/simd/vector_relational.h \
		glm/common.hpp \
		glm/exponential.hpp \
		glm/ext.hpp \
		glm/fwd.hpp \
		glm/geometric.hpp \
		glm/glm.hpp \
		glm/integer.hpp \
		glm/mat2x2.hpp \
		glm/mat2x3.hpp \
		glm/mat2x4.hpp \
		glm/mat3x2.hpp \
		glm/mat3x3.hpp \
		glm/mat3x4.hpp \
		glm/mat4x2.hpp \
		glm/mat4x3.hpp \
		glm/mat4x4.hpp \
		glm/matrix.hpp \
		glm/packing.hpp \
		glm/trigonometric.hpp \
		glm/vec2.hpp \
		glm/vec3.hpp \
		glm/vec4.hpp \
		glm/vector_relational.hpp \
		cfmainwindow.h \
	prevdialog/cfprevdialog.h \
	module/fileopt/cffileopt.h \
	module/modulemanagement/cfmm.h \
	module/basemodules/cfbasemodule.h \
	errorhandler/cferrorhandler.h \
	errorhandler/cferror.hpp \
    module/fftopt/cffftopt.h \
    dockwidget/cfeffectdock.h \
    dockwidget/shadowwidget/cfshadowwidget.h \
    dockwidget/effectwidget/cfeffectwidget.h \
    dockwidget/bkgwidget/cfbkgwidget.h \
    dockwidget/hangupwidget/cfhangupwidget.h \
    dockwidget/fillwidget/cffillwidget.h \
    dockwidget/commonwidget/colorbkg/cfcolorbkg.h \
    dockwidget/commonwidget/colorbkg/cfcolorpreviewpanel.h \
    dockwidget/commonwidget/colorbkg/cfcolorselectpanel.h \
    dockwidget/commonwidget/gradientwidget/lineargradientwidget/cflineargradientwidget.h \
    dockwidget/commonwidget/gradientwidget/cfgradientwidget.h \
    dockwidget/commonwidget/imgwidget/cfimgwidget.h \
    dockwidget/borderwidget/cfborderwidget.h \
    dockwidget/preparedwidget/cfpreparedwidget.h \
    dockwidget/cfresentchardock.h \
    operatorwidget/cfoperatorwidget.h \
    common/cfpassable.h \
    common/funcargs/cfargs.h \
    operatorwidget/cfoperatortab.h \
    dialog/importdialog/cfimportttfdialog.h \
    dialog/importdialog/cfimportindexcell.h \
    dialog/previewwidget/cfpreviewwidget.h \
    module/openglopt/cfopenglopt.h \
    common/pagewidget/PageWidget.h \
    module/xmlopt/cfxmlopt.h \
    dialog/fftlibprevwidget/cffftlibprevwidget.h \
	operatorwidget/cfgllinewidget.h \
    module/queryopt/cfqueryopt.h \
    common/funcargs/cfaligndefine.h

FORMS    += cfmainwindow.ui \
    common/pagewidget/PageWidget.ui

mac {
	INCLUDEPATH += /usr/local/include/freetype2
	LIBS +=	/usr/local/lib/libfreetype.6.dylib
}

DISTFILES +=

RESOURCES += \
	res.qrc
