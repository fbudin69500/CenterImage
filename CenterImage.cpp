#include <itkImage.h>
#include <string>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkDiffusionTensor3D.h>


itk::Point< double , 3 > ComputeNewOrigin( itk::Point< double , 3 > corner ,
                                          itk::Point< double , 3 > origin
                                        )
{

  itk::Point< double, 3 > newOrigin ;
  for( int i = 0 ; i < 3 ; i++ )
  {
    newOrigin[ i ] = ( origin[ i ] - corner[ i ] ) / 2.0 ;
  }
  return newOrigin ;
}


template< class PixelType >
int DTI( std::string input , std::string output )
{
  typedef itk::Image< itk::DiffusionTensor3D< PixelType > , 3 > ImageType ;
  typedef itk::ImageFileReader< ImageType > ReaderType ;
  typedef itk::ImageFileWriter< ImageType > WriterType ;
  //reads input diffusion volume
  typename ReaderType::Pointer reader = ReaderType::New() ;
  reader->SetFileName( input.c_str() ) ;
  reader->Update() ;
  typename ImageType::Pointer image = reader->GetOutput() ;
  image->DisconnectPipeline() ;
  typename ImageType::SizeType size ;
  size = image->GetLargestPossibleRegion().GetSize() ;
  typename ImageType::PointType origin ;
  origin = image->GetOrigin() ;
  itk::Index< 3 > index ;
  for( int i = 0 ; i < 3 ; i++ )
  {
    index[ i ] = size[ i ] - 1 ;
  }
  itk::Point< double , 3 > corner ;
  image->TransformIndexToPhysicalPoint( index , corner ) ;
  image->SetOrigin( ComputeNewOrigin( corner , origin ) ) ;
  typename WriterType::Pointer writer = WriterType::New() ;
  writer->SetFileName( output.c_str() ) ;
  writer->SetInput( image ) ;
  writer->UseCompressionOn() ;
  writer->Update() ;
  return 0 ;
}




template< class PixelType >
int Scalar( std::string input , std::string output )
{
  typedef itk::Image< PixelType , 3 > ImageType ;
  typedef itk::ImageFileReader< ImageType > ReaderType ;
  typedef itk::ImageFileWriter< ImageType > WriterType ;
  //reads input diffusion volume
  typename ReaderType::Pointer reader = ReaderType::New() ;
  reader->SetFileName( input.c_str() ) ;
  reader->Update() ;
  typename ImageType::Pointer image = reader->GetOutput() ;
  image->DisconnectPipeline() ;
  typename ImageType::SizeType size ;
  size = image->GetLargestPossibleRegion().GetSize() ;
  typename ImageType::PointType origin ;
  origin = image->GetOrigin() ;
  itk::Index< 3 > index ;
  for( int i = 0 ; i < 3 ; i++ )
  {
    index[ i ] = size[ i ] - 1 ;
  }
  itk::Point< double , 3 > corner ;
  image->TransformIndexToPhysicalPoint( index , corner ) ;
  image->SetOrigin( ComputeNewOrigin( corner , origin ) ) ;
  typename WriterType::Pointer writer = WriterType::New() ;
  writer->SetFileName( output.c_str() ) ;
  writer->SetInput( image ) ;
  writer->UseCompressionOn() ;
  writer->Update() ;
  return 0 ;
}

//What pixeltype is the image 
void GetImageType( std::string fileName ,
                   itk::ImageIOBase::IOPixelType &pixelType ,
                   itk::ImageIOBase::IOComponentType &componentType )
{
  typedef itk::Image< unsigned char , 3 > ImageType ;
  itk::ImageFileReader< ImageType >::Pointer imageReader =
    itk::ImageFileReader< ImageType >::New();
  imageReader->SetFileName( fileName.c_str() ) ;
  imageReader->UpdateOutputInformation() ;
  pixelType = imageReader->GetImageIO()->GetPixelType() ;
  componentType = imageReader->GetImageIO()->GetComponentType() ;
}


int main( int argc , char* argv[] )
{
  if( argc != 3 )
{
  std::cout<< argv[ 0 ] << " inputVolume outputVolume" << std::endl ;
  return 1 ;
}
  std::string input ;
  input.assign( argv[ 1 ] ) ;
  std::string output ;
  output.assign( argv[ 2 ] ) ;
  itk::ImageIOBase::IOPixelType pixelType ;
  itk::ImageIOBase::IOComponentType componentType ;
  //Check the input image pixel type
  GetImageType( input , pixelType , componentType ) ;
  if( pixelType == itk::ImageIOBase::SYMMETRICSECONDRANKTENSOR
   || pixelType == itk::ImageIOBase::DIFFUSIONTENSOR3D
   || pixelType == itk::ImageIOBase::VECTOR
    )
  {
  switch( componentType )
    {
    case itk::ImageIOBase::UCHAR :
      return DTI< unsigned char > ( input , output ) ;
      break ;
    case itk::ImageIOBase::CHAR :
      return DTI< char > ( input , output ) ;
      break ;
    case itk::ImageIOBase::USHORT :
      return DTI< unsigned short >( input , output ) ;
      break ;
    case itk::ImageIOBase::SHORT :
      return DTI< short > ( input , output ) ;
      break ;
    case itk::ImageIOBase::UINT :
      return DTI< unsigned int > ( input , output ) ;
      break ;
    case itk::ImageIOBase::INT :
      return DTI< int > ( input , output ) ;
      break ;
    case itk::ImageIOBase::ULONG :
      return DTI< unsigned long > ( input , output ) ;
      break ;
    case itk::ImageIOBase::LONG :
      return DTI< long > ( input , output ) ;
      break ;
    case itk::ImageIOBase::FLOAT :
      return DTI< float > ( input , output ) ;
      break ;
    case itk::ImageIOBase::DOUBLE :
      return DTI< double > ( input , output ) ;
      break ;
    case itk::ImageIOBase::UNKNOWNCOMPONENTTYPE:
    default :
      std::cerr<< "unknown component type" << std::endl ;
      break ;
  }
}
else
{
  switch( componentType )
    {
    case itk::ImageIOBase::UCHAR :
      return Scalar< unsigned char > ( input , output ) ;
      break ;
    case itk::ImageIOBase::CHAR :
      return Scalar< char > ( input , output ) ;
      break ;
    case itk::ImageIOBase::USHORT :
      return Scalar< unsigned short >( input , output ) ;
      break ;
    case itk::ImageIOBase::SHORT :
      return Scalar< short > ( input , output ) ;
      break ;
    case itk::ImageIOBase::UINT :
      return Scalar< unsigned int > ( input , output ) ;
      break ;
    case itk::ImageIOBase::INT :
      return Scalar< int > ( input , output ) ;
      break ;
    case itk::ImageIOBase::ULONG :
      return Scalar< unsigned long > ( input , output ) ;
      break ;
    case itk::ImageIOBase::LONG :
      return Scalar< long > ( input , output ) ;
      break ;
    case itk::ImageIOBase::FLOAT :
      return Scalar< float > ( input , output ) ;
      break ;
    case itk::ImageIOBase::DOUBLE :
      return Scalar< double > ( input , output ) ;
      break ;
    case itk::ImageIOBase::UNKNOWNCOMPONENTTYPE:
    default :
      std::cerr<< "unknown component type" << std::endl ;
      break ;
    }
  }
  return 0 ;
}
