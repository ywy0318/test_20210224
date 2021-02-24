package OCC_TPA_TOOL;

import java.io.FileInputStream;
import java.io.IOException;


/**
 * 演示解码器调用方法。一个最简的迷你播放器：
 * <ol>
 * <li>是 {@link jmp123.decoder.AbstractDecoder AbstractDecoder} 的子类。</li>
 * <li>创建输入流之后初始化解码器。 {@link #open(String) open} 方法内先创建输入流，再调用父类的
 * {@link jmp123.decoder.AbstractDecoder#openDecoder() openDecoder} 方法初始化解码器。</li>
 * <li>重载 {@link jmp123.decoder.AbstractDecoder#fillBuffer(byte[], int, int) fillBuffer}
 * 方法，使解码器能够从输入流获取数据。</li>
 * <li>重载 {@link jmp123.decoder.AbstractDecoder#done() done} 方法，解码结束时作必要的清理，例如关闭输入流等。</li>
 * </ol>
 * <p>
 * @version 0.400
 */
public class MiniPlayer extends AbstractDecoder {
	private FileInputStream fileStream;

	/**
	 * 用指定的音频输出audio创建一个MiniPlayer， 参数只能指定一个，其他必须为null。
	 * @param audio 
	 * @param mp3ToWav 
	 */
	public MiniPlayer(IAudio audio, Mp3ToWav mp3ToWav) {
		super(audio, mp3ToWav);
	}

	/**
	 * 打开输入流并初始化解码器。
	 * @param name MP3文件名。
	 * @return MP3帧头简短信息。
	 * @throws IOException 发生I/O错误。
	 */
	public String open(String name) throws IOException {
		fileStream = new FileInputStream(name);
		//System.out.println(name+"***");
		return super.openDecoder();
	}

	@Override
	protected int fillBuffer(byte[] b, int off, int len) {
		try {
			return fileStream.read(b, off, len);
		} catch (Exception e) {
			return -1;
		}
	}

	@Override
	protected void done() {
		if (fileStream != null) {
			try { fileStream.close(); } catch (IOException e) { }
		}
	}

	public void stop() {
		super.stop();
	}
}