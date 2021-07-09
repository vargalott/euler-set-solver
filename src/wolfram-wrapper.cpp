#pragma warning(push)
#pragma warning(disable:4677)
#pragma warning(disable:4267)
#pragma warning(disable:4506)

#include <euler-set-solver/wolfram-wrapper.hpp>

#pragma managed

System::String^ __InvokingCLR::PrepareQuery::Evaluate(System::String^ input)
{
	System::String^ _new_in;
	for (int i = 0; i < input->Length; ++i)
	{
		if (i < input->Length - 1)
			if (System::Char::IsUpper(input[i]) && System::Char::IsUpper(input[i + 1]))
			{
				_new_in += input[i];
				continue;
			};
		_new_in += input[i] + " ";
	};
	auto in_list = __InvokingCLR::Converter::__cli_str_to_list(_new_in);

	System::String^ query;
	for each (auto elem in in_list)
	{
		if (elem == "u")
		{
			query += " union ";
			continue;
		};
		if (elem == "n")
		{
			query += " intersect ";
			continue;
		};
		if (elem == "+")
		{
			query += " symmetric difference  ";
			continue;
		};
		if (elem == "\\")
		{
			query += " difference ";
			continue;
		};
		if (elem == "|")
		{
			query += " complement ";
			continue;
		};
		query += elem;
	};
	return query;
};

System::Drawing::Image^ __InvokingCLR::ResultImage::GetImage(System::String^ url)
{
	auto client = gcnew System::Net::WebClient();
	auto data = client->DownloadData(url);
	auto memory_stream = gcnew System::IO::MemoryStream(data);
	return System::Drawing::Image::FromStream(memory_stream);
}
System::Drawing::Bitmap^ __InvokingCLR::ResultImage::ResizeImage(System::Drawing::Image^ image, int width)
{
	System::Drawing::Bitmap^ bitmap = gcnew System::Drawing::Bitmap(image);
	auto height = cli::safe_cast<int>(System::Math::Ceiling(cli::safe_cast<double>(bitmap->Height * width) / bitmap->Width));
	return gcnew System::Drawing::Bitmap(bitmap, width, (height / 2) + (width / 4));
}
void __InvokingCLR::ResultImage::PrintAscii(System::Drawing::Bitmap^ bitmap)
{
	bool is_toogle = false;
	auto ascii = gcnew array<System::String^> { "#", "#", "@", "%", "=", "+", "*", ":", "-", ".", " " };

	for (int h = 0; h < bitmap->Height; h++)
	{
		for (int w = 0; w < bitmap->Width; w++)
		{
			System::Drawing::Color pixel_color = bitmap->GetPixel(w, h);

			int red = (pixel_color.R + pixel_color.G + pixel_color.B) / 3;
			int green = (pixel_color.R + pixel_color.G + pixel_color.B) / 3;
			int blue = (pixel_color.R + pixel_color.G + pixel_color.B) / 3;

			System::Drawing::Color gray_color = System::Drawing::Color::FromArgb(red, green, blue);

			if (!is_toogle)
			{
				int index = (gray_color.R * 10) / 255;
				if ((pixel_color.R <= 255 && pixel_color.R >= 240) &&
					(pixel_color.G <= 238 && pixel_color.G >= 228) &&
					(pixel_color.B <= 220 && pixel_color.B >= 200))
					Colorful::Console::Write(ascii[index], System::Drawing::Color::Red);
				else
					Colorful::Console::Write(ascii[index], System::Drawing::Color::White);
			};
		};
		if (!is_toogle)
		{
			is_toogle = true;
		}
		else
			is_toogle = false;
	};
	System::Console::WriteLine("\n");
};

void __InvokingCLR::UseWolframAPI::SendRequest(System::String^ unevaluated_query)
{
	System::String^ query = PrepareQuery::Evaluate(unevaluated_query);

	Wolfram::Alpha::WolframAlphaService^ service = gcnew Wolfram::Alpha::WolframAlphaService("");
	Wolfram::Alpha::Models::WolframAlphaRequest^ request = gcnew Wolfram::Alpha::Models::WolframAlphaRequest{ query };
	this->query_result = service->Compute(request);
};
System::String^ __InvokingCLR::UseWolframAPI::GetVennUrl(void)
{
	this->query_result->Wait();
	if (this->query_result->Result->QueryResult->Pods != nullptr)
		return this->query_result->Result->QueryResult->Pods[1]->SubPods[0]->Image->Src;
	return nullptr;
};
void __InvokingCLR::UseWolframAPI::PrintAscii(System::String^ image_url)
{
	if (image_url == nullptr)
	{
		System::Console::WriteLine("Cannot display Venn diagram");
		return;
	};
	auto image = ResultImage::GetImage(image_url);
	auto bitmap = ResultImage::ResizeImage(image, System::Console::WindowWidth);
	ResultImage::PrintAscii(bitmap);
};

#pragma unmanaged
#pragma warning(pop)
